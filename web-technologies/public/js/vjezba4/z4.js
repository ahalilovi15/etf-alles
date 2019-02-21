document.getElementById("dugme").addEventListener("click", () => {
    let teskt = document.getElementById("tekst").value;
    teskt = teskt.replace(/for\s+\((.+);(.+);(.+)\)\s+(\{[^\}]+)(\})/g, `$1;
    while($2)$4$3;
    $5`);

    console.log(teskt);
    teskt = teskt.replaceAll("&amp;", "&");
    teskt = teskt.replaceAll("&nbsp;", " ");
    teskt = teskt.replaceAll("&quot;", "\"\"");
    document.getElementById("tekst").value = teskt;
});

String.prototype.replaceAll = function (search, replacement) {
    var target = this;
    for (let i = 0; i < search.length; ++i) {}
    return target.replace(new RegExp(search, 'g'), replacement);
};