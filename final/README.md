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

## Design Choices

I tried to keep the project small but still full-stack so I could practice different parts of web development.

- **Flask + Jinja instead of a heavier framework**  
  I chose Flask because it feels close to what we used in CS50 (routes, templates, helpers). It’s simple enough for a small quiz app but still lets me separate logic (`app.py`, `questions.py`) from presentation (`templates/`).

- **In-memory questions module instead of a database**  
  All questions live in `questions.py` as a Python list of dictionaries. For this small project, a real database felt like overkill. Storing questions in code made it easier to tweak clues and add/remove questions quickly.

- **Sessions for game state**  
  I use Flask’s `session` to track which question IDs have already been asked, and the user’s `correct` and `total` score for the current round. That way the user can refresh the page or move through questions without losing their progress, and I don’t have to store anything in a database.

- **Multiple accepted answers and simple normalization**  
  Each question has a list of acceptable answers (like `"messi"`, `"leo messi"`, `"lionel messi"`). Before checking, I lowercase the user’s guess, strip it from extra whitespaces, and compare it against those options, so small differences in capitalization or phrasing still count as correct.

- **Keyboard-friendly UX with a tiny bit of JavaScript**  
  I wanted the quiz to be playable almost entirely from the keyboard. The JS in `static/main.js` listens for the Enter key: the first Enter submits the guess, and once a result is shown, pressing Enter again triggers the “Next question” form. This made it feel faster and more “game-like”.

- **No repeat questions per round**  
  Each round keeps a list of `asked_ids` in the session. When choosing the next question, the app filters out ones that were already asked. When the user finishes all questions, the app shows a summary and a “Play again” button that resets the session state.

- **Simple two-page layout with shared styling**  
  Both the quiz page and the About page extend the same `layout.html`, which keeps the header, navigation, and Barça-inspired colors consistent. This also let me practice using template inheritance instead of copy-pasting HTML.



## How to run
- Clone repository
- Create virtual enviornment, from terminal (macOS): python -m venv .venv + + source .venv/bin/activate
- Install dependencies: pip install -r requirements.txt
- Run Flask: flask run
- Visit browser page that generates
