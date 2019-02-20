const char MAIN_page[] PROGMEM = R"=====(
<!DOCTYPE html>
<html>
<head>
<meta http-equiv="refresh" content="3”>
<title>IoT Distance Measuring System</title>
<style>
div.card {
  width: 250px;
  box-shadow: 0 4px 8px 0 rgba(0, 0, 0, 0.2), 0 6px 20px 0 rgba(0, 0, 0, 0.19);
  text-align: center;
  border-radius: 5px;
  background-color: #F08080;	
}

div.header {
    background-color: #F08080;
    color: white;
    padding: 10px;
    font-size: 40px;
    border-radius: 5px;
}

div.container {
    padding: 4px; 
}
</style>
</head>
<body>

<center><h2>IoT Distance Measuring System</h2>

<div class="card">
  <div class="header">
    <h1>Distance from object is: </h1>
  </div>

  <div class="container">
    <h2>@@temp@@ cm</h2>
  </div>
</div>
<a href="https://inventone.ng">Visit Us: inventone.ng</a>
</center>
</body>
</html>

)=====";