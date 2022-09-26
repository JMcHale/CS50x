from flask import redirect, session
from functools import wraps

#login required function checks users is logged in before allowing access
def login_required(f):
    """
    Decorate routes to require login.

    https://flask.palletsprojects.com/en/1.1.x/patterns/viewdecorators/
    """
    #wraps copies whatever is in the function before the decorator is applied, making sure it's tracable during debugging
    @wraps(f)
    def decorated_function(*args, **kwargs):
        #session will need a user_id to allow access, as it means they are logged in
        if session.get("user_id") is None:
            return redirect("/login")
        return f(*args, **kwargs)
    return decorated_function