import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from tempfile import mkdtemp
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")

# Make sure API key is set
if not os.environ.get("API_KEY"):
    raise RuntimeError("API_KEY not set")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/")
@login_required
def index():
    """Show portfolio of stocks"""

    #get the stocks the user owns
    stocks = db.execute("SELECT *, SUM(shares)  FROM stocks WHERE userid = ? GROUP BY symbol;", session["user_id"])
    print(stocks)

    #add the current price for each stock to the stocks list of dicts, by looping through each dict in the stocks list of dicts, and add a new key:value pair of symbol and symbol price
    for stock in stocks:
        stock['price']=lookup(stock["symbol"])["price"]
    print(stocks)

    #Need to add total cash the user has left
    cashleft = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
    print(cashleft)

    stockvalue = 0
    #Need to add the total money the user has, if they have their current cash and the cash worth of all the stocks they own
    for stock in stocks:
        stockvalue = stockvalue + stock["SUM(shares)"] * stock["price"]
    print(stockvalue)

    totalvalue = stockvalue + cashleft[0]["cash"]

    return render_template ("index.html", stocks=stocks, cashleft=cashleft, totalvalue=totalvalue)


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        #user bought a stock

        symbol = request.form.get("symbol")

        #check user input a symbol
        if not symbol:
            return apology("must provide a ticker/symbol", 400)

        sharedata = lookup(request.form.get("symbol"))
        print(sharedata)

        if sharedata == None:
            return apology("stock/symbol does not exist", 400)

        price = sharedata['price']

        shares = request.form.get("shares")

        #check users input a positive integer number of shares
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("must provide positive integer for shares bought", 400)
        except ValueError:
            return apology("must provide a number", 400)

        #inserts the purchase into the purchase table in finance.db
        db.execute("INSERT INTO transactions (userid, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?)", session["user_id"], symbol, shares, sharedata['price'], "buy")

        # need to check the user has enough cash and if not tell them they don't
        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])
        print (cash[0]['cash'])
        print (sharedata['price'])
        print (sharedata['price'] * shares)
        if not cash[0]['cash'] >= sharedata['price'] * shares:
            return apology("you don't have enough money!", 400)


        # need to remove the purchase cost from the users cash if they have the money
        leftcash = cash[0]['cash'] - sharedata['price'] * shares
        db.execute("UPDATE users SET cash = ? WHERE id = ?", leftcash, session["user_id"])

        stocklist = db.execute("SELECT symbol FROM stocks WHERE userid = ?", session["user_id"])
        print (stocklist)

        stockrepeat = 0
        for stockie in stocklist:
            if stockie["symbol"] == symbol:
                stockrepeat = 1
                #the symbol is already present, add to stocks then update
                #get the number of current shares in stocks database
                sharenumber = db.execute("SELECT shares FROM stocks WHERE userid = ? AND symbol = ?", session["user_id"], symbol)
                print(sharenumber)
                sharenumber[0]["shares"] = sharenumber[0]["shares"] + shares
                print(sharenumber)
                db.execute("UPDATE stocks SET shares = ? WHERE userid = ? AND symbol = ?", sharenumber[0]["shares"], session["user_id"], symbol)
                break

        #if duplicate stock wasn't detected, insert a new
        if stockrepeat == 0:
            db.execute("INSERT INTO stocks (userid, symbol, shares) VALUES (?, ?, ?)", session["user_id"], symbol, shares)

        return redirect("/")

    else:
        #user is looking at buying a stock
        return render_template ("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    list = db.execute("SELECT * FROM transactions WHERE userid = ?", session["user_id"])
    print(list)
    return render_template ("history.html", list=list)

    return apology("TODO")


@app.route("/login", methods=["GET", "POST"])
def login():
    """Log user in"""

    # Forget any user_id
    session.clear()

    # User reached route via POST (as by submitting a form via POST)
    if request.method == "POST":

        # Ensure username was submitted
        if not request.form.get("username"):
            return apology("must provide username", 400)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 400)

        # Query database for username
        rows = db.execute("SELECT * FROM users WHERE username = ?", request.form.get("username"))

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
    """Get stock quote."""
    if request.method == "POST":
        if not request.form.get("symbol"):
            return apology("must provide username", 400)

        sharedata = lookup(request.form.get("symbol"))
        print(sharedata)

        if sharedata == None:
            return apology("stock/symbol does not exist", 400)

        symbol = request.form.get("symbol")
        quote = lookup(symbol)
        print(quote)
        return render_template("quoted.html", quote=quote)
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        #user is sending their sensitive details and has clicked login

        #get username variable
        username = request.form.get("username")

        #get users from users database
        users = db.execute("SELECT username FROM users")
        print(users)
        print(username)

        # Ensure username was submitted
        if not username:
            return apology("must provide username for registration", 400)

        #check username is unique, by going through each dict in the users list and seeing if the username is inside
        for dict in users:
            if dict['username'] == username:
                return apology("username taken", 400)

        # Ensure password was submitted
        if not request.form.get("password"):
            return apology("must provide password for registration", 400)

        if not request.form.get("confirmation"):
            return apology("must provide password confirmation for registration", 400)

        password = request.form.get("password")
        password2 = request.form.get("confirmation")

        #NEED TO CHECK FOR PASSWORD CONFIRMATION
        if password != password2:
            return apology("password confirmation must match", 400)

        #MAKE PASSWORD INTO A HASH
        passwordhash = generate_password_hash(password)

        # Insert values into database
        db.execute("INSERT INTO users (username, hash) VALUES (?, ?)", username, passwordhash)

        # Redirect user to home page
        return redirect("/")

    else:
        #user is attempting to register and has reached via the URL itself using GET method
        return render_template("register.html")
    return apology("TODO")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    if request.method == "POST":
        soldstock = request.form.get("symbol")

        #check user input a symbol
        if not soldstock:
            return apology("must provide a ticker/symbol", 400)

        sharedata = lookup(request.form.get("symbol"))
        print(sharedata)

        if sharedata == None:
            return apology("stock/symbol does not exist", 400)

        shares = request.form.get("shares")

        #check users input a positive integer number of shares
        try:
            shares = int(shares)
            if shares <= 0:
                return apology("must provide positive integer for shares bought", 400)
        except ValueError:
            return apology("must provide a number", 400)

        stocks = db.execute("SELECT *, SUM(shares) FROM stocks WHERE userid = ? AND symbol = ?", session["user_id"], soldstock)

        for stock in stocks:
            if stock["shares"] < shares:
                print(stock["shares"])
                return apology("you don't have that many shares", 400)

        db.execute("INSERT INTO transactions (userid, symbol, shares, price, type) VALUES (?, ?, ?, ?, ?)", session["user_id"], soldstock, shares, sharedata['price'], "sell")

        stocklist = db.execute("SELECT symbol FROM stocks WHERE userid = ?", session["user_id"])
        print (stocklist)

        for stockie in stocklist:
            if stockie["symbol"] == soldstock:
                #the symbol is already present, add to stocks then update
                #get the number of current shares in stocks database
                sharenumber = db.execute("SELECT shares FROM stocks WHERE userid = ? AND symbol = ?", session["user_id"], soldstock)
                print(sharenumber)
                sharenumber[0]["shares"] = sharenumber[0]["shares"] - shares
                print(sharenumber)
                db.execute("UPDATE stocks SET shares = ? WHERE userid = ? AND symbol = ?", sharenumber[0]["shares"], session["user_id"], soldstock)
                if sharenumber[0]["shares"] == 0:
                    db.execute("DELETE FROM stocks WHERE userid = ? AND symbol = ?", session["user_id"], soldstock)
                break

        cash = db.execute("SELECT cash FROM users WHERE id = ?", session["user_id"])

        leftcash = cash[0]['cash'] + sharedata['price'] * shares
        db.execute("UPDATE users SET cash = ? WHERE id = ?", leftcash, session["user_id"])

        return redirect("/")

    else:
        stocks = db.execute("SELECT *, SUM(shares)  FROM stocks WHERE userid = ? GROUP BY symbol;", session["user_id"])
        print (stocks)
        return render_template ("sell.html", stocks=stocks)

@app.route("/changepassword", methods=["GET", "POST"])
@login_required
def changepassword():
    if request.method  == "POST":
        password = request.form.get("password")
        password2 = request.form.get("password2")

        if not request.form.get("password"):
            return apology("must provide password", 403)

        if not request.form.get("password2"):
            return apology("must provide password confirmation", 403)

        if password != password2:
            return apology("password confirmation must match", 403)

        passwordhash = generate_password_hash(password)

        db.execute("UPDATE users SET hash = ? WHERE id = ?", passwordhash, session["user_id"])

        return redirect("/")

    else:
        return render_template ("changepassword.html")