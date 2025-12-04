import random

QUESTIONS = [
    {
        "id": 1,
        "clue": "I'm the all-time goal scorer for FC Barcelona and wear number 10.",
        "answers": ["messi", "leo messi", "lionel messi"],
    },
    {
        "id": 2,
        "clue": "I’m a midfielder who joined from Ajax, wear number 21, and many see me as key to Barça’s midfield.",
        "answers": ["frenkie de jong", "de jong", "frenkie"],
    },
    {
        "id": 3,
        "clue": "I wore the number 10 after Messi and play on the left wing. I am spanish and do not currently play for Barça.",
        "answers": ["fati", "ansu", "ansu fati"]
    },
    {
        "id": 4,
        "clue": "In what year was FC Barcelona founded?",
        "answers": ["1899"]
    },
    {
        "id": 5,
        "clue": "Which German coach is in charge of FC Barcelona’s men’s first team for the 2025–26 season?",
        "answers": ["hansi","flick","hansi flick"]
    },
    {
        "id": 6,
        "clue": "Barça’s iconic number 10 shirt is now worn by a teenager from La Masia who plays on the wing. What’s his name?",
        "answers": ["lamine yamal","lamine","yamal"]
    },
    {
        "id": 7,
        "clue": "In June 2025, Barça signed a new goalkeeper by activating his release clause from local rivals Espanyol. Who is he?",
        "answers": ["joan","garcia","joan garcia"]
    },
    {
        "id": 8,
        "clue": "Which English forward joined Barcelona on loan from Manchester United for the 2025–26 season and wears the number 14 shirt?",
        "answers": ["marcus","rashford","marcus rashford"]
    },
    {
        "id": 9,
        "clue": "Which young Spanish centre-back, a La Masia product, wears the number 5 shirt for Barça in the 2025–26 season?",
        "answers": ["pau","cubarsi","pau cubarsi"]
    },
    {
        "id": 10,
        "clue": "Which energetic Spanish midfielder, wearing the number 16 shirt, scored a Champions League hat-trick against Olympiacos this season?",
        "answers": ["fermin","lopez","fermin lopez"]
    },
    {
        "id": 11,
        "clue": "Which Dutch midfielder wearing number 21 recently extended his Barcelona contract until 2029?",
        "answers": ["frenkie de jong", "de jong", "frenkie"]
    },
]

def get_question_by_id(qid: int):
    for q in QUESTIONS:
        if q["id"] == qid:
            return q
    return None

def choose_next_question(asked_ids): 
    remaining = [q for q in QUESTIONS if q["id"] not in asked_ids]
    if not remaining:
        return None
    return random.choice(remaining)