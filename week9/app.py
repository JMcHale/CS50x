#include flask!
from flask import Flask, render_template, request

#create a flask app from THIS file - __name__ represents the current file
app = Flask(__name__)

#a decorator that modifies a function, here modifying the "route" function in the "app" object to recieve the "/" string as an input, essentially adding it to the route for flask
@app.route("/")

#define the index function as a function that returns the file "index.html", run through the render_template function, which must convert index.html to a flask "template"
def index():
    #creates the name variable and sets its value to the value of the key "name", using the args command that represents ?name=david, as an example. David would be the name value here
    return render_template("index.html")

#When the route starts with /greet
@app.route("/greet", methods=["POST"])
def greet():
    #sets the namevar variable to the value that is stored in the "nameof" key, visible in the URL. If they type nothing it will display "person?" instead
    namevar = request.form.get("nameof", "person?")

    #renders the greet.html file where the nameuser variable in the html page is set to the namevar variable in this python script
    return render_template("greet.html", nameuser=namevar)