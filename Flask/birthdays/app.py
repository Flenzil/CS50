import os

from cs50 import SQL
from flask import Flask, flash, jsonify, redirect, render_template, request, session

# Configure application
app = Flask(__name__)
app.jinja_env.filters['zip'] = zip

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///birthdays.db")


@app.after_request
def after_request(response):
    """Ensure responses aren't cached"""
    response.headers["Cache-Control"] = "no-cache, no-store, must-revalidate"
    response.headers["Expires"] = 0
    response.headers["Pragma"] = "no-cache"
    return response


@app.route("/", methods=["GET", "POST"])
def index():
    if request.method == "POST":

        # TODO: Add the user's entry into the database
        new_name = request.form.get("name")
        new_day = request.form.get("day")
        new_month = request.form.get("month")

        db.execute("INSERT INTO birthdays (name, day, month) VALUES (?, ?, ?)", new_name, new_day, new_month)

        return redirect("/")

    else:

        # TODO: Display the entries in the database on index.html
        names = db.execute('SELECT name FROM birthdays')
        days = db.execute('SELECT day FROM birthdays')
        months = db.execute('SELECT month FROM birthdays')

        dates = [f'{day['day']}/{month['month']}' for day, month in zip(days, months)]
        names = [name['name'] for name in names]

        bdays = [[name, date] for name, date in zip(names, dates)]

        return render_template("index.html", bdays = bdays)


