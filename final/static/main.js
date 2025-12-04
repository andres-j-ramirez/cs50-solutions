// CS50x 2025 Final Project: Barça Quiz
// I used AI-based tools (ChatGPT) to help with parts of the keyboard navigation
// and event-handling logic, but I reviewed and understand all of this code.

// Allow for enter key for next question after a guess
const guessInput = document.querySelector('input[name="guess"]');
const resultElement = document.getElementById('result');
const nextForm = document.getElementById('next-form');

document.addEventListener("keydown", function (event) {
    console.log("keydown:", event.key, "activeElement:", document.activeElement);

    if (
        event.key === "Enter" &&
        document.activeElement === guessInput &&
        resultElement &&
        resultElement.textContent.trim().length > 0
    ) {
        console.log("Intercepting Enter → going to next question");
        event.preventDefault();
        if (nextForm) {
            nextForm.submit();
        }
    }
});

if (guessInput){
    guessInput.focus();
}

// Same for Play again button at end
