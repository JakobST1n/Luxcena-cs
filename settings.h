const char SETTINGS_page[] PROGMEM = R"=====(
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

        <div class="container-fluid pt-3 pb-3">

            <div id="success-box" class="alert alert-success" role="alert">{{SUCCESSMSG}}</div>

            <div class="alert alert-danger" role="alert">
              <b>Warning:</b> The password-protection does not work yet! Make sure to don´t expose the device.
            </div>

            <div class="card card-inverse bg-dark text-white mt-3">
                <div class="card-body">

                    <div class="card-title">
                        <h3>Password</h3>
                    </div>

                    <div class="container">
                        <form>

                            <h5 class="small text-muted">To change any settings, you must enter the correct password"</h5>
                            <div class="form-group row">

                                <div class="col-sm-12">
                                    <input type="password" class="form-control" id="" placeholder="Device password" readonly>
                                </div>
                            </div>

                        </form>
                    </div>

                </div>
            </div>

            <div class="card card-inverse bg-dark text-white mt-3">
                <div class="card-body">

                    <div class="card-title">
                        <h3>Settings</h3>
                    </div>

                    <div class="container">
                        <form method="post">

                            <input type="hidden" name="type" value="settings">

                            <h5 class="small text-muted">Device settings:</h5>
                            <div class="form-group row">
                                <label for="lblDeviceName" class="col-sm-2 col-form-label">Device name</label>
                                <div class="col-sm-10">
                                    <input type="text" class="form-control" name="txtDeviceName" id="txtDeviceName" placeholder="Ex. Rooflight">
                                </div>
                            </div>

                            <div class="form-group row">
                                <label for="lblDeviceLocation" class="col-sm-2 col-form-label">Location</label>
                                <div class="col-sm-10">
                                    <input type="text" class="form-control" name="txtDeviceLocation" id="txtDeviceLocation" placeholder="Ex. Bathroom">
                                </div>
                            </div>

                            <h5 class="small text-muted">Wifi settings:</h5>
                            <div class="form-group row">
                                <label for="lblSSID" class="col-sm-2 col-form-label">SSID</label>
                                <div class="col-sm-10">
                                    <input type="name" class="form-control" name="txtSSID" id="txtSSID" placeholder="Name of router">
                                </div>
                            </div>

                            <div class="form-group row">
                                <label for="lblPassword" class="col-sm-2 col-form-label">Pasword</label>
                                <div class="col-sm-10">
                                    <input type="name" class="form-control" name="txtPassword" id="txtPassword" placeholder="Passphrase (If open, write nothing)">
                                </div>
                            </div>

                            <div class="form-group row">
                                <div class="col-sm-10">

                                    <button type="submit" class="btn btn-primary">Save</button>
                                    <br /><span class="small text-muted"> <b> Note:</b> The device will reboot and turn of any connected appliances when you save the settings.</span>
                                    <br /><span class="small text-muted"> <b> Note:</b> Empty or unchanged fields will not be updated.</span>
                                </div>
                            </div>

                        </form>
                    </div>

                </div>
            </div>

            <div class="card card-inverse bg-dark text-white mt-3">
                <div class="card-body">

                    <div class="card-title">
                        <h3>Version & OTA</h3>
                    </div>

                    <div class="container">
                        <form>
                            <h5>Device type: <b>clapSensor</b></h5>
                            <h5>Current version: <b>1.0.0</b></h5>
                            <hr />
                            <div class="form-group row">
                                <label for="inputEmail3" class="col-sm-2 col-form-label">Update file:</label>
                                <div class="col-sm-10">
                                    <input type="file" class="form-control-file" id="exampleFormControlFile1">
                                </div>
                            </div>

                            <div class="form-group row">
                                <div class="col-sm-10">
                                    <button type="submit" class="btn btn-danger">Flash new version</button>
                                    <br /><span class="small text-muted"> <b> Note:</b> The device will reboot and turn of any connected appliances when you flash a new version.</span>
                                </div>
                            </div>

                        </form>
                    </div>

                </div>
            </div>
        </div>


        <script src="/script.js" charset="utf-8"></script>
        <script type="text/javascript">
            fixNoNetwork();
            var successAlert = document.getElementById('success-box');

            updatePlaceholder("txtDeviceName", "{{DEVICENAME}}");
            updatePlaceholder("txtDeviceLocation", "{{DEVICELOCATION}}");;

            if (successAlert.innerHTML.length < 1) {
                successAlert.style.display = "none";
            }

            function updatePlaceholder(elemId, textToInsert) {
                var field = document.getElementById(elemId);
                if (textToInsert != "") { field.placeholder = "Curr; " + textToInsert }
            }

        </script>
    </body>

    </html>
)=====";
