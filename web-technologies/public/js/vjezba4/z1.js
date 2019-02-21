let toggler = document.getElementsByClassName("caret");
let i;

for (i = 0; i < toggler.length; i++) {
  toggler[i].addEventListener("click", function() {
    console.log(this.parentElement.querySelector(".nested"));
    this.parentElement.querySelector(".nested").classList.toggle("active");
    this.classList.toggle("kliknuto");
  });
}