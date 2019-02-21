let sabiranje = (document) => {
  const a = Number(document.getElementById('sabirak1').value);
  const b = Number(document.getElementById('sabirak2').value);
  const c = a + b;
  document.getElementById('zbir').value = String(c);
}

let zadatak1 = (document) => {
  let odgovor = prompt("Unesite neki teskt");
  alert(odgovor.split("").reverse().join(""));
}


let zadatak2 = (document) => {


  document.write('<table border="1">');
  let redovi = 11,
    kolone = 11;
  for (i = 0; i < redovi; i++) {

    document.write('<tr>');
    for (j = 0; j < kolone; j++) {
      if (i == 0) document.write('<th>');
      else document.write('<td>');
      if (i == 0 && j == 0) {
        document.write('X');
      } else if (i == 0) document.write(String(j));
      else if (j == 0) document.write(String(i));
      else document.write(String(i * j));
      if (i == 0) document.write('</th>');
      else document.write('</td>');
    }
    document.write('</tr>');
  }
  document.write('</table>');

  // nije rečeno kako da importujemo hehe
  let link = document.createElement('link');
  link.rel = "stylesheet";
  link.type = "text/css";
  link.href = "/css/vjezba3/zadatak2.css";
  document.querySelector("head").appendChild(link);
}
