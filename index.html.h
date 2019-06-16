const String MAIN_page = R"=(
<!DOCTYPE html>
<html>

<head>
    <meta charset='utf-8'>
    <title>Administrador RFID</title>
    <meta name='viewport' content='width=device-width, initial-scale=1'>
</head>

<body>
    <div id="mySidenav" class="sidenav">
        <a href="javascript:void(0)" class="closebtn" onclick="closeNav()">&times;</a>
        <a href="#">Administrar</a>
        <a href="#">Listar</a>
        <a href="#">Clients</a>
        <a href="#">Contact</a>
    </div>
    <span style="font-size:30px;cursor:pointer" onclick="openNav()">&#9776; Menu</span>
    <h1>Administracion RFID</h1>
    <div id="agregar">
        <h2>Agregar nueva llave</h1>
            <button type="button" onclick="agregar()">Agregar</button>
            <br>
            <h2 id="estado"></h2>
    </div>

    <script>
        function agregar() {
            var xhttp = new XMLHttpRequest();
            xhttp.onreadystatechange = function() {
                if (this.readyState == 4 && this.status == 200) {
                    document.getElementById("estado").innerHTML =
                        this.responseText;
                }
            };
            xhttp.open("GET", "agregar", true);
            xhttp.send();
        }

        function openNav() {
            document.getElementById("mySidenav").style.width = "100%";
            document.body.style.backgroundColor = "rgba(0,0,0,0.4)";
        }

        function closeNav() {
            document.getElementById("mySidenav").style.width = "0";
            document.body.style.backgroundColor = "white";
        }
    </script>

    <style>
        h1 {
            text-align: center;
        }
        
        #agregar {
            text-align: center;
            border: black 1px solid;
            width: 20%;
        }
        
        body {
            font-family: "Lato", sans-serif;
            transition: background-color .5s;
        }
        
        .sidenav {
            height: 100%;
            max-width: 275px;
            width: 0;
            position: fixed;
            z-index: 1;
            top: 0;
            left: 0;
            background-color: #111;
            overflow-x: hidden;
            transition: 0.7s;
            padding-top: 60px;
            text-align: center;
        }
        
        .sidenav a {
            padding: 8px 8px 8px 32px;
            text-decoration: none;
            font-size: 25px;
            color: #818181;
            display: block;
            transition: 0.3s;
        }
        
        .sidenav a:hover {
            color: #f1f1f1;
        }
        
        .sidenav .closebtn {
            position: absolute;
            top: 0;
            right: 25px;
            font-size: 36px;
            margin-left: 50px;
        }
        
        @media screen and (max-height: 450px) {
            .sidenav {
                padding-top: 15px;
            }
            .sidenav a {
                font-size: 18px;
            }
        }
        
        @media only screen and (max-width: 375px) {
            .sidenav {
                max-width: 100%;
                transition: 0.5s;
            }
        }
    </style>
</body>

</html>

)=";