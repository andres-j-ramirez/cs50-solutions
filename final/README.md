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


## How to run
- Clone repository
- Create virtual enviornment, from terminal (macOS): python -m venv .venv + + source .venv/bin/activate
- Install dependencies: pip install -r requirements.txt
- Run Flask: flask run
- Visit browser page that generates