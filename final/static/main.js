console.log("main.js loaded");

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
