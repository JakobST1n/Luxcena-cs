const char SETTINGS_page[] PROGMEM = R"=====(
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

        <div class="container-fluid pt-3 pb-3">

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
                                    <input type="password" class="form-control" id="name" placeholder="Device password" readonly>
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
                        <form>

                            <h5 class="small text-muted">Device settings:</h5>
                            <div class="form-group row">
                                <label for="inputEmail3" class="col-sm-2 col-form-label">Device name</label>
                                <div class="col-sm-10">
                                    <input type="name" class="form-control" id="name" placeholder="Rooflight">
                                </div>
                            </div>

                            <div class="form-group row">
                                <label for="inputEmail3" class="col-sm-2 col-form-label">Location</label>
                                <div class="col-sm-10">
                                    <input type="name" class="form-control" id="name" placeholder="Bathroom">
                                </div>
                            </div>

                            <h5 class="small text-muted">Wifi settings:</h5>
                            <div class="form-group row">
                                <label for="inputEmail3" class="col-sm-2 col-form-label">SSID</label>
                                <div class="col-sm-10">
                                    <input type="name" class="form-control" id="name" placeholder="Name of router">
                                </div>
                            </div>

                            <div class="form-group row">
                                <label for="inputEmail3" class="col-sm-2 col-form-label">Pasword</label>
                                <div class="col-sm-10">
                                    <input type="name" class="form-control" id="name" placeholder="Passphrase (If open, write nothing)">
                                </div>
                            </div>

                            <div class="form-group row">
                                <div class="col-sm-10">

                                    <button type="submit" class="btn btn-primary">Save</button>
                                    <button type="submit" class="btn btn-muted">Cancel</button>
                                    <br /><span class="small text-muted"> <b> Note:</b> The device will reboot and turn of any connected appliances when you save the settings.</span>
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

    </body>

    </html>
)=====";
