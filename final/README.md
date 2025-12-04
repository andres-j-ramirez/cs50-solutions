# Barça Quiz
#### Video Demo: <URL HERE>
#### Description:

# Barça Quiz

This is my final project for CS50: a small web app where you answer quiz questions about FC Barcelona.

It won’t change the world or solve a big problem, but it’s something I take interest in and built for fun, and it can entertain my wife and me for a little while. I learned a lot building it end-to-end.

## Features

- Random Barça quiz questions about players and club history  
- No repeated questions within a round  
- Score tracking: correct / total per round  
- Keyboard-friendly flow:
  - Enter submits your guess
  - Enter again advances to the next question
- “Play again” button to restart a fresh round  
- Separate About page explaining the project  

## Technologies

- Python 3
- Flask
- Jinja templates
- HTML, CSS, JavaScript
- Browser sessions for tracking state

## Project Structure

All of the code for the project lives in this "final" folder:

- `app.py`  
  The main Flask application. It defines the routes (`/` for the quiz and `/about` for the info page), handles form submissions, picks questions, tracks score with the session, and renders the templates.

- `questions.py`  
  Contains the list of Barça questions and answers as Python data. It also has helper functions to look up a question by its ID and to choose the next question that hasn’t been asked yet.

- `templates/layout.html`  
  Base HTML layout for the whole site. It includes the `<head>`, main header (“Barça Quiz”), nav links, and a `{% block body %}` that the other pages fill in.

- `templates/index.html`  
  The main quiz page. Shows the current question, the score for this round, the result (“Correct!” or “Incorrect!”), the guess form, and the “Next question” button.

- `templates/about.html`  
  The About page. Explains why I built the project and some technical details about how it works.

- `static/styles.css`  
  All the styling for the site: dark background, Barça-inspired colors, typography, spacing, the quiz card box, and button styles for the primary (blue) and secondary (maroon) buttons.

- `static/main.js`  
  Small bit of JavaScript that improves keyboard navigation. It lets you press Enter once to submit your guess and (after the result shows) press Enter again to trigger the “Next question” button automatically.

- `requirements.txt`  
  Python dependencies needed to run the app (Flask and its related packages).

- `README.md`  
  This file. Describes the project, how it works, and how to run it.


## How to run
- Clone repository
- Create virtual enviornment, from terminal (macOS): python -m venv .venv + + source .venv/bin/activate
- Install dependencies: pip install -r requirements.txt
- Run Flask: flask run
- Visit browser page that generates
