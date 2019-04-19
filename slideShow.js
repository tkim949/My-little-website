/* Left and Right arrow for the slide show */

let goSlides = document.querySelectorAll(".slides");
let arrowLeft = document.querySelector(".leftArrow");
let arrowRight = document.querySelector(".rightArrow");

var current = 0;
function clear() {
  for(let i =0; i <goSlides.length; i++) {
      goSlides[i].style.display ="none";
  }
}
// Start
function startSlide() {
 clear();
  goSlides[0].style.display = "block";
}
// Show prev
function slideLeft() {
  clear();
  goSlides[current - 1].style.display = "block";
  current--;
}
// Show next
function slideRight() {
  clear();
  goSlides[current + 1].style.display = "block";
  current++;
}

// Left arrow click
arrowLeft.addEventListener("click", function() {
  if (current === 0) {
    current = goSlides.length;
  }
  slideLeft();
});

// Right arrow click
arrowRight.addEventListener("click", function() {
  if (current === goSlides.length - 1) {
    current = -1;
  }
  slideRight();
});

startSlide();

/* For auto slideshow */

var slideNum = 1;

showSlidesByClick(slideNum);

function showSlidesByClick(n) {
    var i;

    if (n > goSlides.length) {
            slideNum = 1 }
    if (n < 1) {
            slideNum = goSlides.length}

    for (i = 0; i < goSlides.length; i++) {
        goSlides[i].style.display = "none";
    }

   goSlides[slideNum-1].style.display = "block";

}

function autoSlides(){
    slideNum++;
    showSlidesByClick(slideNum);
    setTimeout(autoSlides, 3100);
}

document.querySelector('.buttonDiv button').addEventListener('click', () => {
    autoSlides();
});
