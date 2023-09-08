var color;
var BGC;
function HoverOn(a) {
    color = a.style.color;
    BGC = a.style.backgroundColor;
    a.style.color = "#aaa";
    a.style.backgroundColor = "black";
}
function HoverOff(a) {
    a.style.color = color;
    a.style.backgroundColor = BGC;
}

const text = "#Suggesting U Songs#";
let index = 0;
let isTyping = false;

function type() {
    document.getElementById("WebName").innerHTML += text.charAt(index);
    index++;
    if (index >= text.length) {
        clearInterval(interval);
    }
}

const observer = new IntersectionObserver(entries => {
    if (entries[0].isIntersecting && !isTyping) {
        isTyping = true;
        const interval = setInterval(type, 100);
        document.getElementById("WebName").style.opacity = 1;
    }
});

observer.observe(document.getElementById("WebName"));

let i = 0;
function autoclick() {
    document.getElementsByClassName("next")[i].click();
    i = (i+1)%4;
    // console.log("Hello");
}
setInterval(autoclick,4000);