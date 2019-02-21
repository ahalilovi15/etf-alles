window.onload = function () {
    document.getElementById('mojelement').style.fontWeight = "bold";
    // postavljamo css stil font-weight na bold
}

function pritisnut() {
    var x = document.getElementById('izmjena');
    x.value = "Prikazi"; // pristup atributu elementa
    document.getElementById('mojelement').style.display = "none";
    return false; // osigurava da link ne bude izvrsen
}

function klikDugme(referenca) { // pristup elementu preko this > blah
    if (referenca.value === "Sakrij") {
        // postavi CSS property display na vrijednost “none”
        document.getElementById('mojelement').style.display = "none";
        referenca.value = "Prikazi";
        return false;
    }

    referenca.value = "Sakrij";
    // Pristup DIV elementu mojelement preko DOM stabla
    var z = document.body.children[0];
    // ili s obzirom da je DOM stablo prvi element je DIV ispod body taga
    z = document.body.children.mojelement;
    // moze i ovako ili document.body.children['mojelement']
    z = document['body']['children']['mojelement'];
    // moze i ovako pa cak i window['document'] :)
    z.style.display = "block"; // prikazi ga ili z['style']['display'] = ...
}