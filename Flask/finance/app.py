import os

from cs50 import SQL
from flask import Flask, flash, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

from helpers import apology, login_required, lookup, usd

# Configure application
app = Flask(__name__)

# Custom filter
app.jinja_env.filters["usd"] = usd

# Configure session to use filesystem (instead of signed cookies)
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///finance.db")


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
    id = session["user_id"]
    stocks = db.execute("SELECT symbol FROM stocks WHERE id IS ?", id)
    amounts = db.execute("SELECT amount FROM stocks WHERE id IS ?", id)
    cash = db.execute("SELECT cash FROM users WHERE id IS ?", id)[0]["cash"]

    stocks = [i["symbol"] for i in stocks]
    amounts = [i["amount"] for i in amounts]

    prices = []
    for stock in stocks:
        prices.append(lookup(stock)["price"])

    values = [price * amount for price, amount in zip(prices, amounts)]

    total = cash
    for price, amount in zip(prices, amounts):
        total += price * amount

    info = []
    for stock, amount, price, value in zip(stocks, amounts, prices, values):
        d = {}
        d["stock"] = stock
        d["amount"] = amount
        d["price"] = usd(price)
        d["value"] = usd(value)
        info.append(d)

    return render_template("index.html", info=info, total=usd(total), cash=usd(cash))


@app.route("/buy", methods=["GET", "POST"])
@login_required
def buy():
    """Buy shares of stock"""
    if request.method == "POST":
        id = session["user_id"]
        symbol = request.form.get("symbol")

        quote_dict = lookup(symbol)
        if quote_dict is None:
            return apology("Symbol does not exist")

        amount = request.form.get("shares")
        try:
            amount = float(amount)
        except ValueError:
            return apology("Amount of shares must be a number!")

        if amount % 1:
            return apology("Amount of shares must be a whole number!")

        if amount < 0:
            return apology("Amount of shares must be positive!")

        current_money = db.execute("SELECT cash FROM users WHERE id IS ?", id)[0][
            "cash"
        ]
        try:
            current_amount = db.execute(
                "SELECT amount FROM stocks WHERE id IS ? AND symbol IS ?", id, symbol
            )[0]["amount"]
        except IndexError:
            current_amount = 0

        cost = int(amount) * quote_dict["price"]

        if current_money >= cost:
            if current_amount > 0:
                db.execute(
                    "UPDATE stocks SET amount = ? WHERE id IS ? AND symbol IS ?",
                    current_amount + amount,
                    id,
                    quote_dict["symbol"],
                )
            else:
                db.execute(
                    "INSERT INTO stocks (id, symbol, amount) VALUES (?, ?, ?)",
                    id,
                    quote_dict["symbol"],
                    current_amount + amount,
                )

            db.execute(
                "UPDATE users SET cash = ? WHERE id IS ?", current_money - cost, id
            )
            db.execute(
                "INSERT INTO history (id, symbol, amount, type, value) VALUES (?, ?, ?, ?, ?)",
                id,
                quote_dict["symbol"],
                amount,
                "Buy",
                cost,
            )
            return redirect("/")

        else:
            return apology("Not enough funds")
    else:
        return render_template("buy.html")


@app.route("/history")
@login_required
def history():
    """Show history of transactions"""
    id = session["user_id"]
    stocks = db.execute("SELECT symbol FROM history WHERE id IS ?", id)
    amounts = db.execute("SELECT amount FROM history WHERE id IS ?", id)
    types = db.execute("SELECT type FROM history WHERE id IS ?", id)
    values = db.execute("SELECT value FROM history WHERE id IS ?", id)

    stocks = [i["symbol"] for i in stocks][::-1]
    amounts = [i["amount"] for i in amounts][::-1]
    types = [i["type"] for i in types][::-1]
    values = [i["value"] for i in values][::-1]

    info = []
    for stock, amount, _type, value in zip(stocks, amounts, types, values):
        d = {}
        d["stock"] = stock
        d["amount"] = amount
        d["type"] = _type
        if _type == "Buy":
            d["value"] = f"-{usd(value)}"
        else:
            d["value"] = usd(value)
        info.append(d)

    return render_template("history.html", info=info)
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
            return apology("must provide username", 403)

        # Ensure password was submitted
        elif not request.form.get("password"):
            return apology("must provide password", 403)

        # Query database for username
        rows = db.execute(
            "SELECT * FROM users WHERE username = ?", request.form.get("username")
        )

        # Ensure username exists and password is correct
        if len(rows) != 1 or not check_password_hash(
            rows[0]["hash"], request.form.get("password")
        ):
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
        symbol = request.form.get("symbol")
        quote_dict = lookup(symbol)
        if quote_dict is None:
            return apology("Symbol does not exist")
        return render_template(
            "quote.html", name=quote_dict["name"], price=usd(quote_dict["price"])
        )
    else:
        return render_template("quote.html")


@app.route("/register", methods=["GET", "POST"])
def register():
    """Register user"""
    if request.method == "POST":
        username = request.form.get("username")
        password = request.form.get("password")
        password_c = request.form.get("confirmation")

        if any([username == "", password == "", password_c == ""]):
            return apology("Please complete all forms")

        if password != password_c:
            return apology("Password did not match confirmation")

        if db.execute("SELECT * FROM users WHERE username = ?", username):
            return apology("Username already exists!")

        password_hash = generate_password_hash(password)

        db.execute(
            "INSERT INTO users (username, hash) VALUES (?, ?)", username, password_hash
        )
        rows = db.execute("SELECT * FROM users WHERE username = ?", username)
        session["user_id"] = rows[0]["id"]
        return redirect("/")
    else:
        return render_template("register.html")


@app.route("/sell", methods=["GET", "POST"])
@login_required
def sell():
    """Sell shares of stock"""
    id = session["user_id"]
    if request.method == "POST":
        stock = request.form.get("symbol")
        amount = request.form.get("shares")

        if amount is None or stock is None:
            return apology("All forms must be filled!")
        try:
            amount = float(amount)
        except ValueError:
            return apology("Amount of shares must be a number!")

        if amount % 1:
            return apology("Amount of shares must be a whole number!")

        if amount < 0:
            return apology("Amount of shares must be positive!")

        value = lookup(stock)["price"]
        # raise Exception(value)

        current_amount = db.execute(
            "SELECT amount FROM stocks WHERE id IS ? AND symbol IS ?", id, stock
        )[0]["amount"]
        current_cash = db.execute("SELECT cash FROM users WHERE id IS ?", id)[0]["cash"]

        if amount > current_amount:
            return apology("Can't sell more shares than you have!")

        amount = min(current_amount, amount)

        if amount == current_amount:
            db.execute("DELETE FROM stocks WHERE id IS ? AND symbol IS ?", id, stock)
        else:
            db.execute(
                "UPDATE stocks SET amount = ? WHERE id IS ? AND symbol IS ?",
                current_amount - amount,
                id,
                stock,
            )

        db.execute(
            "UPDATE users SET cash = ? WHERE id IS ?", current_cash + amount * value, id
        )
        db.execute(
            "INSERT INTO history (id, symbol, amount, type, value) VALUES (?, ?, ?, ?, ?)",
            id,
            stock,
            amount,
            "Sell",
            amount * value,
        )
        return redirect("/")
    else:
        stocks = db.execute("SELECT symbol FROM stocks WHERE id IS ?", id)
        stocks = [i["symbol"] for i in stocks]

        return render_template("sell.html", options=stocks)
