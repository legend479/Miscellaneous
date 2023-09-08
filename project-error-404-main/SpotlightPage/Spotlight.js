var currentRating = 0;
var ratings = {};
var reviews = {};

function setRating(rating) {
    currentRating = rating;
    for (var i = 1; i <= 5; ++i) {
        var star = document.getElementById('star' + i);
        if (i <= rating) {
            star.src = 'stars2.png';
        } else {
            star.src = 'stars1.png';
        }
    }
}

function addRating() {
    var name = document.getElementById('name').value;
    if (name == '') {
        alert('Please enter your name.');
        return;
    }
    if (currentRating == 0) {
        alert('Please select a rating.');
        return;
    }
    ratings[name] = currentRating;
    reviews[name] = document.getElementById('review').value;
    updateTable();
    updateAverageRating();
    resetForm();
}

function updateTable() {
    var tableBody = document.querySelector('#ratings-table tbody');
    tableBody.innerHTML = '';
    for (var i = 0; i < Object.values(ratings).length; i++) {
        var row = tableBody.insertRow();
        var nameCell = row.insertCell();
        var ratingCell = row.insertCell();
        var reivewCell = row.insertCell();
        nameCell.textContent = Object.keys(ratings)[i];
        // console.log(Object.keys(ratings)[i]);
        ratingCell.textContent = Object.values(ratings)[i];
        // console.log(Object.values(ratings)[i]);
        reivewCell.textContent = Object.values(reviews)[i];
    }
}

function updateAverageRating() {
    var totalRating = 0;
    for (var i = 0; i < Object.values(ratings).length; i++) {
        totalRating += Object.values(ratings)[i];
    }
    var averageRating = totalRating / Object.values(ratings).length;
    document.getElementById('average-rating').textContent = averageRating.toFixed(1);
}

function resetForm() {
    currentRating = 0;
    for (var i = 1; i <= 5; i++) {
        var star = document.getElementById('star' + i);
        star.src = 'stars1.png';
    }
    document.getElementById('name').value = '';
    document.getElementById('review').value = '';
}


// Set the date we're counting down to
var countDownDate = new Date("30 June 2023 00:00").getTime();

// Update the countdown every 1 second
var x = setInterval(function () {

    // Get the current date and time
    var now = new Date().getTime();

    // Calculate the distance between now and the countdown date
    var distance = countDownDate - now;

    // Calculate days, hours, minutes and seconds
    var days = Math.floor(distance / (1000 * 60 * 60 * 24));
    var hours = Math.floor((distance % (1000 * 60 * 60 * 24)) / (1000 * 60 * 60));
    var minutes = Math.floor((distance % (1000 * 60 * 60)) / (1000 * 60));
    var seconds = Math.floor((distance % (1000 * 60)) / 1000);

    // Output the result in an element with id="countdown"
    document.getElementById("countdown").innerHTML = days + "d " + hours + "h "
        + minutes + "m " + seconds + "s ";

    // If the countdown is over, show a message
    if (distance < 0) {
        clearInterval(x);
        document.getElementById("countdown").innerHTML = "Released";
    }
}, 1000);


var image = document.getElementById("SpotlightImg");
function zoomIn() {
    image.style.transform = "scale(1.2)";
    image.style.transition = "transform 1s ease";
    setTimeout(zoomOut, 1000);
}
function zoomOut() {
    image.style.transform = "scale(1)";
    image.style.transition = "transform 1s ease";
    setTimeout(zoomIn, 1000);
}
zoomIn();

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