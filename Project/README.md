# Quest-It

#### Video Demo:  https://www.youtube.com/watch?v=I3Km6pL5ums

#### Description:

A todo app that aims for simplicity and the least amount of effort possible to get to your next todo. It tells you what to do next based on your location and the project you want to work on, with no faff in between. It then also records what you have done, and the time it took you. This can then be used to assign users "levels", if developed further this webapp would include a series of difficulties and levels that reward the user for completing their tasks, this could be enhanced with a physical reward, leaderboard, etc....

This uses the following Frameworks and languages:
- Flask/Python
- Jinja
- HTML
- CSS
- SQLite3
- Javascript

Each page uses the layout.html template, and through Jinja templating repeats essentials like the navbar and stylesheet linking

The user can register at register.html, this adds their records to the sql table

The user logs in at login.html, and will be redirected here if they are not logged in

When logged in, the user is presented with the tasks they individually have through the use of sessions

They can add a task using newtask.html, this includes location, the day they want to do it on, and if they want it to repeat. Days are recorded using bits, where a series of 7 bits represents which days the task wants to be done on. This enables storing multiple values in one key, to extra these values, you then use bitwise arithmetic to compare what each bit is. Then on nexttask.html, a query can be run to only select the days that return true from the SQL store of days in bit form. If this wasn't done you would need several more keys to store each day value, and much more code.

The user can view a list of tasks on index.html, and refresh the tasks that are to repeat

They can then view their next task, based on where they are and what day it is, along with what project they want to work on, using nexttask.html. You can enter notes on the task as you complete it, and then submit the task once complete. This is then stored in the SQL database. The user clicks on the recording time button to record how much time the task takes, simply click the button again if you take a break. This is done using javascript in the HTML file

You can view a history of the tasks completed in history.html, and the time it took, this can be filtered according to location and project.

Finally, level.html gives the user what level they are depending on the difficulty they want

