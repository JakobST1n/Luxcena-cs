const char MAIN_page[] PROGMEM = R"=====(
    <!DOCTYPE html>
    <html>

        <head>
            <meta charset="utf-8">
            <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

            <title>{{NAME}}</title>

            <link href="https://maxcdn.bootstrapcdn.com/bootstrap/4.0.0-beta/css/bootstrap.min.css" rel="stylesheet" integrity="sha384-/Y6pD6FV/Vv2HJnA6t+vslU6fwYXjCFtcEpHbNJ0lyAFsXTsjBbfaDjzALeQsN6M" crossorigin="anonymous">
            <link rel="stylesheet" href="./style.css">
        </head>


        <body>

            <nav class="navbar navbar-dark bg-dark">
                <a class="navbar-brand" href="/">IOT Device</a>
                <a class="navbar-toggler navbar-toggler-right" href="/settings">
                    &#9881;
                </a>
            </nav>

            <div class="container-fluid pt-3">

                    <div class="card card-inverse bg-dark text-white">
                      <div class="card-body">

                        <div class="card-title">
                            <h3>
                                {{NAME}}
                                <span class="text-align:right;">
                                    <label class="switch float-right">
                                      <input type="checkbox" id="lampActive">
                                      <span class="slider round"></span>
                                    </label>
                                </span>
                            </h3>
                        </div>
                        <h6 class="card-subtitle mb-2 text-muted">{{Location}}</h6>

                        <hr />
                        <div class="toggle-button toggle-button--tuli">
                            <input id="sensorActive" type="checkbox">
                            <label for="sensorActive">Clap sensor</label>
                            <div class="toggle-button__icon"></div>
                        </div>

                      </div>
                    </div>

            </div>


            <script type="text/javascript">
                document.getElementById("lampActive").addEventListener("change", changLampState);
                document.getElementById("sensorActive").addEventListener("change", changSensorState);
                setInterval(getStates, 1000);

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

                function changLampState() {
                    var boxState = document.getElementById("lampActive").checked;
                    if (boxState) {
                        ajax_request("/j/lamp/1", function(e) {
                            console.log(e);
                        });
                    } else {
                        ajax_request("/j/lamp/0", function(e) {
                            console.log(e);
                        });
                    }
                }

                function changSensorState() {
                    var sensorState = document.getElementById("sensorActive").checked;
                    if (sensorState) {
                        ajax_request("/j/sens/1", function(e) {
                            console.log(e);
                        });
                    } else {
                        ajax_request("/j/sens/0", function(e) {
                            console.log(e);
                        });
                    }
                }

                function getStates() {
                    ajax_request("/j/", function(e) {
                        result = JSON.parse(e);

                        var lampOn = false;
                        var sensorOn = false;
                        if (result['lampOn'] == 1) { lampOn = true; }
                        if (result['sensorOn'] == 1) { sensorOn = true; }

                        document.getElementById("lampActive").checked = lampOn;
                        document.getElementById("sensorActive").checked = sensorOn;
                    });
                }
            </script>
        </body>

    </html>

)=====";
