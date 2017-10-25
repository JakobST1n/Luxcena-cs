const char MAIN_page[] PROGMEM = R"=====(
    <!DOCTYPE html>
    <html>

        <head>
            <meta charset="utf-8">
            <meta name="viewport" content="width=device-width, initial-scale=1, shrink-to-fit=no">

            <title>{{NAME}}</title>

            {{BOOTSTRAPLINK}}
            <link rel="stylesheet" href="./style.css">
        </head>


        <body>

            <nav class="navbar navbar-dark bg-dark">
                <a id="homePageAddr" class="navbar-brand" href="/">IOT Device</a>
                <a id="settingsPageAddr" class="navbar-toggler navbar-toggler-right" href="/settings">
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
                                      <input type="checkbox" id="lampActive" {{LAMPACTIVECHECKED}}>
                                      <span class="slider round"></span>
                                    </label>
                                </span>
                            </h3>
                        </div>
                        <h6 class="card-subtitle mb-2 text-muted">{{Location}}</h6>

                        <hr />
                        <div class="toggle-button toggle-button--tuli">
                            <input id="sensorActive" type="checkbox" {{SENSORCHECKED}}>
                            <label for="sensorActive">Clap sensor</label>
                            <div class="toggle-button__icon"></div>
                        </div>

                      </div>
                    </div>

            </div>


            <script src="/script.js" charset="utf-8"></script>
            <script type="text/javascript">
                fixNoNetwork();
                var pollingActive = true;  // Prevent states from being updated while trying to change them.
                document.getElementById("lampActive").addEventListener("change", changLampState);
                document.getElementById("sensorActive").addEventListener("change", changSensorState);
                setInterval(getStates, 1000);

                function changLampState() {
                    var boxState = document.getElementById("lampActive").checked;
                    if (boxState) {
                        pollingActive = false;
                        ajax_request("/j?lamp=1", function(e) {
                            pollingActive = true;
                            console.log(e);
                        });
                    } else {
                        pollingActive = false;
                        ajax_request("/j?lamp=0", function(e) {
                            pollingActive = true;
                            console.log(e);
                        });
                    }
                }

                function changSensorState() {
                    var sensorState = document.getElementById("sensorActive").checked;
                    if (sensorState) {
                        pollingActive = false;
                        ajax_request("/j?sens=1", function(e) {
                            pollingActive = true;
                            console.log(e);
                        });
                    } else {
                        pollingActive = false;
                        ajax_request("/j?sens=0", function(e) {
                            pollingActive = true;
                            console.log(e);
                        });
                    }
                }

                function getStates() {
                    if (pollingActive) {
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
                }
            </script>
        </body>

    </html>
)=====";
