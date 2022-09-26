import time

#using cs50 sqlite3 library
from cs50 import SQL

#flask needed for app to work, render_template needed to render a page, redirect to redirect, request to get what method GET or POST is required, session to store details on users
from flask import Flask, redirect, render_template, request, session
from flask_session import Session
from werkzeug.security import check_password_hash, generate_password_hash

#helpers contains our login_required decorator
from helpers import login_required

#gives the app the name of the file we are in, so it can run it
app = Flask(__name__)

# Ensure templates are auto-reloaded
app.config["TEMPLATES_AUTO_RELOAD"] = True

# Configure CS50 Library to use SQLite database
db = SQL("sqlite:///questit.db")

#sets the secret key for security
app.config.update(SECRET_KEY='osd(99092=36&462134kjKDhuIS_d23')

@app.template_filter('ctime')
def timectime(value):
    return time.ctime(value) # datetime.datetime.fromtimestamp(s)

#decorator that puts the render_template html file in the response to a URL that is in the route
@app.route("/", methods=["GET","POST"])
@login_required
def index():
    if request.method == "POST":
        if request.form.get("taskbut"):
            #user has decided to delete a dynamic task
            taskID = request.form.get("taskbut")

            #Remove the task from the dynamic database
            db.execute("DELETE FROM tasks WHERE userID = ? AND taskID = ? LIMIT 1", session["user_id"], taskID)

        if request.form.get("reptaskbut"):
            #user has decided to delete a repeated task
            taskID = request.form.get("reptaskbut")

            #Remove the task from the dynamic database
            db.execute("DELETE FROM tasks WHERE userID = ? AND taskID = ? LIMIT 1", session["user_id"], taskID)

            #also remove task from repeated database
            db.execute("DELETE FROM repeattasks WHERE userID = ? AND taskID = ? LIMIT 1", session["user_id"], taskID)

        if request.form.get("refresh"):
            #if the user clicks refresh tasks, go through and replace any tasks that are missing/have been completed, but need repeating. User should click this after finishing a week?
            #need to first check if any tasks are missing from the dynamic table, that are in repeattasks. The taskID should match!
            tasks = db.execute("SELECT * FROM tasks WHERE userID = ?", session["user_id"])
            repeattasks = db.execute("SELECT * FROM repeattasks WHERE userID = ?", session["user_id"])
            print(tasks)
            print(repeattasks)

            #loop through repeated tasks, and check to see if that task is missing from dynamic tasks, if it is, insert it back into dynamic tasks
            for repeattask in repeattasks:
                taskin = 0
                for task in tasks:
                    if task["taskID"] == repeattask["taskID"]:
                        print("? is already in the dynamic table!", repeattask["taskID"])
                        taskin = 1
                        break
                if taskin != 1:
                    print("? is not in the table and needs adding!", repeattask["taskID"])

                    db.execute("INSERT INTO tasks (taskID, task, userID, location, days) VALUES (?, ?, ?, ?, ?)", repeattask["taskID"], repeattask["task"], session["user_id"], repeattask["location"], repeattask["days"])

        return redirect("/")

    else:
        #variables need refreshing from any changes upon load, dynamic table recieving repeated tasks
        tasks = db.execute("SELECT * FROM tasks WHERE userID = ?", session["user_id"])
        repeattasks = db.execute("SELECT * FROM repeattasks WHERE userID = ?", session["user_id"])

        return render_template("index.html", tasks=tasks, repeattasks=repeattasks)

@app.route("/history", methods=["GET", "POST"])
@login_required
def history():
    if request.method == "POST":
        #user has clicked a filter, show only what the filter is
        if request.form.get("taskselect"):
            task = request.form.get("taskselect")
            tasks = db.execute("SELECT * FROM taskscomplete WHERE userID = ? AND task = ?", session["user_id"], task)
            print("only task")

        if request.form.get("locationselect"):
            location = request.form.get("locationselect")
            tasks = db.execute("SELECT * FROM taskscomplete WHERE userID = ? AND location = ?", session["user_id"], location)
            print("only location")

        #want to make it so you can apply multiple filters
        if request.form.get("taskselect") and request.form.get("locationselect"):
            task = request.form.get("taskselect")
            location = request.form.get("locationselect")
            tasks = db.execute("SELECT * FROM taskscomplete WHERE userID = ? AND task = ? AND location = ?", session["user_id"], task, location)
            print("BOTH!")

        taskselect = db.execute("SELECT DISTINCT task FROM taskscomplete WHERE userID = ?", session["user_id"])
        print(taskselect)

        locationselect = db.execute("SELECT DISTINCT location FROM taskscomplete WHERE userID = ?", session["user_id"])
        print(locationselect)

        return render_template("history.html", tasks=tasks, taskselect=taskselect, locationselect=locationselect)

    else:
        #user has not clicked a filter so show all tasks
        #show a history of all the tasks the user has completed
        tasks = db.execute("SELECT * FROM taskscomplete WHERE userID = ?", session["user_id"])

        for task in tasks:
            if  task["timeelapsed"] == None:
                print(task["timeelapsed"])
            else:
                task["timeelapsed"] = int(task["timeelapsed"] / 1000)

        #unique tasks for the select form to filter by task
        taskselect = db.execute("SELECT DISTINCT task FROM taskscomplete WHERE userID = ?", session["user_id"])
        print(taskselect)

        locationselect = db.execute("SELECT DISTINCT location FROM taskscomplete WHERE userID = ?", session["user_id"])
        print(locationselect)

        return render_template("history.html", tasks=tasks, taskselect=taskselect, locationselect=locationselect)

@app.route("/register", methods=["GET", "POST"])
def register():
    if request.method == "POST":
        #Register the user
        username = request.form.get("username")

        #check for no duplicates first
        users = db.execute("SELECT username FROM users")
        print(users)
        print(username)

        # Ensure username was submitted
        if not username:
            #TODO -  return custom error
            print("No username")
            return redirect("/register")

        #loop through the dicts in the users linked lists of dicts
        for dict in users:
            if dict['username'] == username:
                #TODO -  return custom error
                print("User not unique")
                return redirect("/register")

        # Ensure password was submitted
        if not request.form.get("password"):
            print("No password")
            return redirect("/register")

        # Ensure password was confirmed
        if not request.form.get("passwordconfirmation"):
            print("No password confirmation")
            return redirect("/register")

        #collect variables to check passwords match
        password = request.form.get("password")
        print(password)
        passwordconfirmation = request.form.get("passwordconfirmation")
        print(passwordconfirmation)

        #Check passwords match
        if password != passwordconfirmation:
            print("Passwords don't match")
            return redirect("/register")

        #MAKE PASSWORD INTO A HASH
        passwordhash = generate_password_hash(password)

        # Insert values into database
        db.execute("INSERT INTO users (username, password) VALUES (?, ?)", username, passwordhash)

        #Return user to homepage
        return redirect("/")

    else:
        #Route reached via GET method, so show user registration page
        return render_template("register.html")

@app.route("/login", methods=["GET", "POST"])
def login():
    if request.method == "POST":
        #user just submitted login details

        #assign entered username to username variable
        username = request.form.get("username")

        #assign entered password to password variable
        password = request.form.get("password")

        if not username:
            print ("didn't enter a username")
            return redirect("/")

        if not password:
            print ("didn't enter a password")
            return redirect("/")

        # Check if username is in database
        user = db.execute("SELECT * FROM users WHERE username = ?", username)
        print(user)

        if len(user) != 1 or not check_password_hash(user[0]["password"], password):
            #user login failed
            print ("user details wrong")
            return redirect("/")

        session["user_id"] = user[0]["userID"]

        return redirect("/")
    else:
        #user has gone to the login page and is trying to log in
        return render_template("login.html")

@app.route("/logout")
def logout():
    """Log user out"""

    # Forget any user_id
    session.clear()

    # Redirect user to login form
    return redirect("/")

@app.route("/newtask", methods=["GET", "POST"])
@login_required
def newtask():
    if request.method == "POST":
        #user has entered a task
        task = request.form.get("task")
        location = request.form.get("location")

        if not request.form.get("location"):
            #user hasn't entered a location, simply redirect
            print("location needed")
            return redirect("/newtask")

        # I am using bits to represent days, instead of a string lookup - sun = 1 (00000001), mon=2 (00000010), tue=4 (00000100), wed=8 (00001000), thu=16 (00010000), fri=32 (00100000), sat=64 (01000000)
        # adding these bits togethers simply changes a 0 to a 1, if the task taskes place on every day the binary would be 01111111, or 127 in decimal
        # you can then compare the location of each bit with the & bitwise operator to find out if a day is present in the response
        days = request.form.getlist("days")
        print(days)

        #sum all the values to store as a single value in the database
        daytotal = 0
        for day in days:
            daytotal += int(day)
        print(daytotal)

        if not task:
            print("Task not entered")
            return redirect("/")

        repeat = request.form.get("repeat")
        print(repeat)

        db.execute("INSERT INTO tasks (task, userID, location, days) VALUES (?, ?, ?, ?)", task, session["user_id"], location, daytotal)

        taskID = db.execute("SELECT taskID FROM tasks WHERE userID = ? AND location = ? AND task = ? LIMIT 1", session["user_id"], location, task)
        print(taskID)

        if repeat == "repeat":
            db.execute("INSERT INTO repeattasks (taskID, task, userID, location, days) VALUES (?, ?, ?, ?, ?)", taskID[0]["taskID"], task, session["user_id"], location, daytotal)

        return redirect("/newtask")

    else:
        #user entering a task
        return render_template("newtask.html")

@app.route("/nexttask", methods=["GET", "POST"])
@login_required
def nexttask():
    if request.method == "POST":
        taskID = request.form.get("button")
        print(taskID)

        taskdetails = request.form.get("taskdetails")
        print(taskdetails)

        #get what task this ID represents
        taskdone = db.execute("SELECT * FROM tasks WHERE taskID = ?", taskID)
        print(taskdone)

        #get time task was completed
        tasktime = request.form.get("tasktime")

        #convert milliseconds to seconds, to enable using the "time" python library later for formatting
        tasktime = int(tasktime) / 1000

        #also need this as an integer number, get rid of the trailing decimal values
        tasktime = int(tasktime)
        print(tasktime)

        timeelapsed = request.form.get("timertime")

        if not timeelapsed:
            timeelapsed = 0
        
        print(request.form.get("timertime"))
        print("The time it took was: ", timeelapsed)

        #get info needed from the object returned by the SQL query
        task = taskdone[0]["task"]
        location = taskdone[0]["location"]

        #add the task to the tasks completed database
        db.execute("INSERT INTO taskscomplete (task, userID, location, taskdetails, tasktime, timeelapsed) VALUES (?, ?, ?, ?, ?, ?)", task, session["user_id"], location, taskdetails, tasktime, timeelapsed)

        #Remove the task from the database
        db.execute("DELETE FROM tasks WHERE userID = ? AND taskID = ? LIMIT 1", session["user_id"], taskID)


        #refresh the next task page to load the next task
        return redirect("/nexttask")

    else:
        locationselect = request.args.get("locationselect")
        print(locationselect)
        dayselect = request.args.get("day")
        print(dayselect)

        if not request.args.get("locationselect") and not request.args.get("day"):
            #user has not selected a location or day, so display next task regardless of location
            nexttask = db.execute("SELECT * FROM tasks WHERE userID = ? LIMIT 1", session["user_id"])
            print("user not selected location or day")

        elif request.args.get("locationselect") and not request.args.get("day"):
            #user has selected a location but not a day, display first task in this location, ignore day
            locationselect = request.args.get("locationselect")
            print("user has selected location only")

            nexttask = db.execute("SELECT * FROM tasks WHERE userID = ? AND location = ? LIMIT 1", session["user_id"], locationselect)
            print(nexttask)

        elif request.args.get("day") and not request.args.get("locationselect"):
            #user has selected a location but not a day, display first task in this location, ignore day
            dayselect = request.args.get("day")
            print("user has selected day only")

            nexttask = db.execute("SELECT * FROM tasks WHERE userID = ? AND (days & ?) LIMIT 1", session["user_id"], dayselect)
            print(nexttask)

        else:
            #user has selected a location/day, display the first task in this location and day
            locationselect = request.args.get("locationselect")
            dayselect = request.args.get("day")
            print("user has selected location and day")

            # submit all criteria to find what the next task should be. (days & ?) is bitwise arithmetic to find what days are stored in the days column number.
            # if dayselect isn't in the days column bitwise storage, then it will return a false and the SQL will move to the next entry to check
            nexttask = db.execute("SELECT * FROM tasks WHERE userID = ? AND location = ? AND (days & ?) LIMIT 1", session["user_id"], locationselect, dayselect)
            print(nexttask)

        locations = db.execute("SELECT DISTINCT location FROM tasks WHERE userID = ?", session["user_id"])
        print(locations)

        return render_template("nexttask.html",nexttask=nexttask,locations=locations)

@app.route("/level", methods=["GET","POST"])
@login_required
def level():
    if request.method == "POST":
        lvldiff = request.form.get("lvldiff")
        print(lvldiff)

        settings = db.execute("SELECT * FROM usersettings WHERE userID = ?", session["user_id"])
        if settings:
            print("user already exists")
            db.execute("UPDATE usersettings SET leveldifficulty = ? WHERE userID = ?", lvldiff, session["user_id"])
        else:
            db.execute("INSERT INTO usersettings (userID, leveldifficulty) VALUES (?, ?)", session["user_id"], lvldiff)
            print("user does not exist")

        return redirect("/level")

    leveldata = db.execute("SELECT SUM(timeelapsed) FROM taskscomplete WHERE userID = ?", session["user_id"])
    levelsettings = db.execute("SELECT * FROM usersettings WHERE userID = ?", session["user_id"])
    print(levelsettings)
    print(leveldata[0])

    return render_template("level.html", leveldata=leveldata[0], levelsettings=levelsettings)