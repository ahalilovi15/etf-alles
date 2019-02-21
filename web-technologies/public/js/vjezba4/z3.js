document.getElementById("dugme").addEventListener("click", () => {
    let teskt = document.getElementById("tekst").value;
    teskt = teskt.replace(/<\/?([^>]+)>/g, '$1');
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