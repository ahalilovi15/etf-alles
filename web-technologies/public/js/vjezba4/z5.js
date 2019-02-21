var he;

var table = document.getElementById("myTable");

document.getElementById("dugme").addEventListener("click", () => {
    let teskt = document.getElementById("tekst").value;

    he = teskt.match(/.+(\[.+\])\s\"(.+)\"\s404.+/g);
    console.log(he);

    generate_table();
});

String.prototype.replaceAll = function (search, replacement) {
    var target = this;
    for (let i = 0; i < search.length; ++i) {}
    return target.replace(new RegExp(search, 'g'), replacement);
};


function generate_table() {

    var tables = document.getElementsByTagName("TABLE");
    for (var i = tables.length - 1; i >= 0; i -= 1)
        if (tables[i]) tables[i].parentNode.removeChild(tables[i]);

    // get the reference for the body
    var body = document.getElementsByTagName("body")[0];

    // creates a <table> element and a <tbody> element
    var tbl = document.createElement("table");
    var tblBody = document.createElement("tbody");

    var row = document.createElement("tr");
    var cell = document.createElement("td");
    var cellText = document.createTextNode("Vrijeme greške");
    cell.appendChild(cellText);
    row.appendChild(cell);
    var cell2 = document.createElement("td");
    var cellText2 = document.createTextNode("Lokacija");
    cell2.appendChild(cellText2);
    row.appendChild(cell2);

    // add the row to the end of the table body
    tblBody.appendChild(row);

    // creating all cells
    he.forEach((v, i) => {
        // creates a table row
        var row = document.createElement("tr");

        // Create a <td> element and a text node, make the text
        // node the contents of the <td>, and put the <td> at
        // the end of the table row
        var cell = document.createElement("td");
        var cellText = document.createTextNode(v.replace(/.+\[(.+)\+.+\]\s\"(.+)\"\s404.+/, "$1"));
        cell.appendChild(cellText);
        row.appendChild(cell);
        var cell2 = document.createElement("td");
        var cellText2 = document.createTextNode(v.replace(/.+(\[.+\])\s\"(.+)\"\s404.+/, "$2"));
        cell2.appendChild(cellText2);
        row.appendChild(cell2);

        // add the row to the end of the table body
        tblBody.appendChild(row);
    });

    // put the <tbody> in the <table>
    tbl.appendChild(tblBody);
    // appends <table> into <body>
    body.appendChild(tbl);
    // sets the border attribute of tbl to 2;
    tbl.setAttribute("border", "2");
}