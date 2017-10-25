function fixNoNetwork() {
    if (getParameterByName("l") != null) {
        document.getElementById("homePageAddr").href = "/?l=1";
        document.getElementById("settingsPageAddr").href = "/settings?l=1";
        return;
    }

    try {
        var xhttp = new XMLHttpRequest();
        xhttp.onerror = function onError(e) {
            //alert("Error " + e.target.status + " occurred while receiving the document.");
            var hrefAddr = window.location.href + "?l=1";
            window.location.replace(hrefAddr);
        };
        xhttp.open("GET", "https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta.2/css/bootstrap.min.css", true);
        xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
        xhttp.send();
    } catch (e) {
        console.log(e);
    }
}

function ajax_request(adress, callback_function) {
    /* A simple ajax request wrapper
       DoesnÂ´t return anything else than the callback */
    var xhttp = new XMLHttpRequest();
    xhttp.onreadystatechange = function() {
        if (this.readyState == 4 && this.status == 200) {
            callback_function(this.responseText);
        }
    };
    xhttp.open("POST", adress, true);
    xhttp.setRequestHeader("Content-type", "application/x-www-form-urlencoded");
    xhttp.send();
}

function getParameterByName(name, url) {
    if (!url) url = window.location.href;
    name = name.replace(/[\[\]]/g, "\\$&");
    var regex = new RegExp("[?&]" + name + "(=([^&#]*)|&|#|$)"),
        results = regex.exec(url);
    if (!results) return null;
    if (!results[2]) return '';
    return decodeURIComponent(results[2].replace(/\+/g, " "));
}
