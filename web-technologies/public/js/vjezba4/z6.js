function provjeriFormu() {
	var greska = document.getElementById('greska');
	// ili document.body.children[0]
	greska.innerHTML = ""; // ocistimo prethodne greske

	var forma = document.getElementById('mfid');
	if (forma.ime.value.length > 10 || forma.ime.value.length < 3) {
		greska.innerHTML += "Predugo/prekratko ime<br>";
		return false;
	}

	var prezimeRegex = /^[a-z ,.'-]+$/i;
	if (!prezimeRegex.test(forma['prezime'].value)) {
		greska.innerHTML += "Prezime ne valja<br>";
		return false;
	}

	// nije ispostovan regex traženi u postavci
	var emailRegex = /[A-Z0-9._%+-]+@[A-Z0-9.-]+\.[A-Z]{2,4}/i;
	if (!emailRegex.test(forma['email'].value)) {
		greska.innerHTML += "Email ne valja<br>";
		return false;
	}
	// uraditi 3-4-5 na tutu !!!



	// Ovaj regex ukucajte u regex101.com za tumacenje:
	var telefonRegEx = /^\(?(\d{3})\)?[-]?(\d{3})[-]?(\d{3})$/;
	if (!telefonRegEx.test(forma['telefon'].value)) {
		greska.innerHTML += "Telefon format: (061)-123-345 ili 061-123-456 ili 061123456<br>";
		return false;
	}




	if (!forma.sretan.checked) return false;
	var sel = forma.godina.options[forma.godina.selectedIndex].text;
	// vazan je i .value
	if (sel !== "Druga") return false;

	return true;
}

document.getElementById("mfid").addEventListener("submit",
	provjeriFormu, false);

document.getElementById("stela").addEventListener("click", function (ev) {
	document.forms.mojaforma.submit();
}, false);