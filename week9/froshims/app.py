from flask import Flask, render_template, request, session
from flask_session import Session

app = Flask(__name__)

#initialise a session
app.config["SESSION_PERMANENT"] = False
app.config["SESSION_TYPE"] = "filesystem"
Session(app)

#array for entering the sports a user can select
SPORTSPY = [
    "basketfall",
    "bigballs",
    "manyball",
    "FASTbalL"
]

@app.route("/")
def index():
    return render_template("index.html", sports=SPORTSPY)

@app.route("/register", methods=["POST"])
def register():
    #validate submission
    if not request.form.get("username") or request.form.get("sport") not in SPORTSPY:
        return render_template("failure.html")

    #example of how a session could work
    session["name"] = request.form.get("username")
    nameuser = request.form.get("username")
    sport = request.form.get("sport")
    sportcheck = request.form.getlist("sportcheck")
    return render_template("register.html", nameuser=nameuser, sportuser=sport, sportcheck=sportcheck)