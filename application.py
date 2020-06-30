import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.exceptions import default_exceptions, HTTPException, InternalServerError
from werkzeug.security import check_password_hash, generate_password_hash
from datetime import datetime

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Ensure responses aren't cached
@app.after_request
def after_request(response):
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_FILE_DIR"] = mkdtemp()
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.route("/")
@login_required
def index():
    # Declare var with user id
    userid = session["user_id"]

    # Query database for userid stock and store
    portfolio = db.execute(
        "SELECT symbol, SUM(quantity), name FROM portfolio WHERE userid = :userid GROUP BY symbol", userid=userid)

    # Query database for cash held by userid
    cash = db.execute("SELECT cash FROM users WHERE id= :userid", userid=userid)
    stockprice = None
    rowvalue = None
    # Total porfolio value
    totalvalue = 0
    # Iterate through portfolio
    for row in portfolio:

        # Lookup symbol in row and get price
        currentsymbol = row["symbol"]
        currentprice = lookup(currentsymbol)
        stockprice = currentprice.get("price")

        # Enter current value into portfolio
        row.setdefault("price", stockprice)

        # Calculate value of row
        rowvalue = row["SUM(quantity)"] * row["price"]
        totalvalue = rowvalue + totalvalue

        # Add value of row into portfolio
        row.setdefault("rowvalue", rowvalue)

    # Calculate total value of portfolio
    totalvalue = totalvalue + cash[0]["cash"]
    return render_template("index.html", portfolio=portfolio, cash=cash, stockprice=stockprice, rowvalue=rowvalue, totalvalue=totalvalue)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    # Direct if method is POST or GET
    if request.method == "POST":
        symbol = request.form.get("symbol")

        # Look up stock
        quote = lookup(symbol)

        # Check return is not none
        if quote == None:
            return apology("Stock not found")

        # Get price from returned dict
        price = quote.get("price")

        # Get stock name from returned dict
        name = quote.get("name")

        # Get quantity of shares from form and check valid
        try:
            quantity = int(request.form.get("shares"))
        except ValueError:
            return apology("Please enter an integer..", 400)
        if quantity < 1:
            return apology("Please enter an integer..", 400)

        # Calculate total value of purchase
        value = price * quantity

        # Get username from session
        userid = session["user_id"]

        # Calculate cash figures and store in VAR
        cashavail = db.execute("SELECT cash FROM users WHERE id = :userid", userid=userid)
        usercash = int(cashavail[0]["cash"])
        updateusercash = usercash - value

        # Get current datetime
        now = datetime.now()
        date = now.strftime('%Y-%m-%d %H:%M:%S')

        # Check cash available for user is sufficient
        if value > usercash:
            return apology("Not enough cash..")

        # Insert new purchase into portfolio and subtract value from users cash
        else:
            db.execute("INSERT INTO portfolio (userid, symbol, quantity, name) VALUES(?,?,?,?)",
                    (userid, symbol, quantity, name))
            db.execute("UPDATE users SET cash = :updateusercash WHERE id = :userid", updateusercash=updateusercash, userid=userid)

            # Log into history database
            db.execute("INSERT INTO history (symbol, shares, price, date, userid) VALUES (?,?,?,?,?)",
                    (symbol, quantity, price, date, userid))

            # Return to index
            return redirect("/")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    userid = session["user_id"]
    history = db.execute("SELECT * FROM history WHERE userid = :userid", userid=userid)
    return render_template("history.html", history=history)


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = :username",
                          username=request.form.get("username"))

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(rows[0]["hash"], request.form.get("password")):
            return apology("invalid username and/or password", 403)

        # Remember which user has logged in
        session["user_id"] = rows[0]["id"]

        # Redirect user to home page
        return redirect("/")

    # User reached route via GET (as by clicking a link or via redirect)
    else:
        return render_template("login.html")


@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")


@app.route("/quote", methods=["GET", "POST"])
@login_required
def quote():
    if request.method == "POST":
        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        if quote == None:
            return apology("Stock not found")
        else:
            stock = quote.get("symbol")
            price = quote.get("price")
            return render_template("quoted.html", price=price, stock=stock)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":

        # Hash password from register form
        username = request.form.get("username")
        if not request.form.get("username"):
            return apology("Must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("Must provide password", 400)

        # Ensure passwords mathc
        elif request.form.get("confirmation") != request.form.get("password"):
            return apology("Passwords do not match", 400)

        # Hash password from register form
        passhash = generate_password_hash(request.form.get("password"))

        # heck to see whether username exists
        exist_user = db.execute("SELECT * FROM users WHERE username = :username",
                                username=request.form.get("username"))
        if len(exist_user) > 0:
            return apology("User already exists", 400)

        # Insert username and passhash into db
        db.execute("INSERT INTO users (username, hash) VALUES(?,?)", (username, passhash))
        success = "New User Created"
        return render_template("login.html", success=success)
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        # Get session userid
        userid = session["user_id"]

        # Input data from form
        shares = int(request.form.get("shares"))
        symbol = request.form.get("symbol")

        # Check shares available
        available = db.execute("SELECT SUM(quantity) FROM portfolio WHERE userid = :userid AND symbol = :symbol",
                                userid=userid, symbol=symbol)
        if shares > int(available[0]["SUM(quantity)"]):
            return apology("Insufficent stock held")

        # Lookup current price
        quote = lookup(symbol)
        currentprice = quote.get("price")

        # Calculate value of sell
        salevalue = currentprice * shares

        # Update value of cash and share holding
        db.execute("UPDATE users SET cash = cash + :salevalue WHERE id = :userid", salevalue=salevalue, userid=userid)
        db.execute("UPDATE portfolio SET quantity = (SELECT quantity FROM portfolio WHERE userid = :userid AND symbol = :symbol ORDER BY quantity DESC LIMIT 1) - :shares WHERE userid = :userid AND symbol = :symbol ORDER BY quantity DESC LIMIT 1", userid=userid, symbol=symbol, shares=shares)

        # Update transaction history get current datetime
        negshares = 0 - shares
        now = datetime.now()
        date = now.strftime('%Y-%m-%d %H:%M:%S')
        db.execute("INSERT INTO history (symbol, shares, price, date, userid) VALUES (?,?,?,?,?)",
                (symbol, negshares, currentprice, date, userid))
        return redirect("/")
    else:
        # Get userid from session
        userid = session["user_id"]
        # Check which stocks user holds
        held = db.execute("SELECT symbol FROM portfolio WHERE userid = :userid GROUP by symbol", userid=userid)
        return render_template("sell.html", held=held)


def errorhandler(e):
    """Handle error"""
    if not isinstance(e, HTTPException):
        e = InternalServerError()
    return apology(e.name, e.code)


# Listen for errors
for code in default_exceptions:
    app.errorhandler(code)(errorhandler)