document.getElementById("dugme").addEventListener("click", () => {
    let unosString = document.getElementById("funkcija").value;

    unosString = unosString.replaceAll("-", "+-");

    let dijelovi = unosString.split("+");

    let koeficjenti = [];
    let stepeni = [];
    let brojac = 0;

    dijelovi.forEach(element => {
        let podjela = element.split(/\wx\\^|x| \d+/);
        console.log(podjela);
        if (podjela[0] === "") podjela[0] = "1";
        if (podjela[0] === "-") podjela[0] = "-1";
        koeficjenti[brojac] = podjela[0];
        if (podjela[1] === undefined) podjela[1] = "0";
        if (podjela[1] === "") podjela[1] = "1";
        stepeni[brojac] = podjela[1].replace("^", "");
        brojac += 1;
    });



    let koeficjentiInt = koeficjenti.map(function (x) {
        return parseInt(x, 10);
    });

    let stepeniInt = stepeni.map(function (x) {
        return parseInt(x, 10);
    });

    // imamo koeficjente i stepene
    // slijedi iscrtavanje 
    var c = document.getElementById("slika");
    var ctx = c.getContext("2d");

    var x0 = 250, y0 = 250, R = 5;
    ctx.beginPath();

    for(let i = -200; i<= 200; i++){
        let a = racunajY((i /(y0 /R)), koeficjentiInt, stepeniInt) * (y0/R);
        ctx.lineTo(x0 + i, y0 - a);
    }
    ctx.stroke();
});

function racunajY(x, koef, stepeni) {
    let value = 0;
    for (let i = 0; i < koef.length; ++i) {
        value += koef[i] * Math.pow(x,stepeni[i]);
    }
    return value;
}



String.prototype.replaceAll = function (search, replacement) {
    var target = this;
    return target.split(search).join(replacement);
};
