<!DOCTYPE html>
<html>
    <head>
        <link rel=stylesheet  href=style.css>
        <link rel="preconnect" href="https://fonts.gstatic.com">
        <link href="https://fonts.googleapis.com/css2?family=Roboto:ital,wght@0,700;1,300&display=swap" rel="stylesheet">
        <script src="sorttable.js"></script>

    </head>
<body>

<?php
$counter=0;
$servername = "localhost";
$dbname = "id15493415_distance";
$username = "id15493415_local";
$password = "9WNLADqX+S3P9ZV|";
$conn = new mysqli($servername, $username, $password, $dbname);
if ($conn->connect_error) {
    die("Connection failed: " . $conn->connect_error);
} 
$sql = "SELECT id, sensor, location, value1, reading_time FROM SensorData ORDER BY id DESC";
echo '<table class="sortable">
    <thead>
          <tr> 
            <th>ID</th> 
            <th>Sensor</th> 
            <th>Location</th> 
            <th>Value 1</th> 
            <th>Timestamp</th> 
          </tr>
     </thead>';
if ($result = $conn->query($sql)) {
    while ($row = $result->fetch_assoc()) {
        $row_id = $row["id"];
        $row_sensor = $row["sensor"];
        $row_location = $row["location"];
        $row_value1 = $row["value1"];
        $row_reading_time = $row["reading_time"];
        if($row_value1<2000 and $counter<15)
        echo '<tr> 
                <td>' . $row_id . '</td> 
                <td>' . $row_sensor . '</td> 
                <td>' . $row_location . '</td> 
                <td>' . $row_value1 . '</td> 
                <td>' . $row_reading_time . '</td> 
              </tr>';
              $counter++;
    }
    $result->free();
}
$conn->close();
?> 
</table>
    <div>
        <label for="email">Enter your email:</label>
<input type="email" id="email" name="email">    
<label for="value">Enter threshold:</label>
<input type="value" id="value" name="value"> 
<button name="update" type="button">Update</button>
    </div>

</body>
</html>