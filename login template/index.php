<!DOCTYPE HTML>

<html>




	<head>

            <meta charset="utf-8" />
		<meta name="viewport" content="width=device-width, initial-scale=1" />
    <title>Sign-Up/Login Form</title>


         <link rel="stylesheet" href="https://www.w3schools.com/w3css/4/w3.css">

        <link rel="stylesheet" href="path/to/font-awesome/css/font-awesome.min.css">
        <link rel="stylesheet" href="https://cdnjs.cloudflare.com/ajax/libs/normalize/5.0.0/normalize.min.css">

             <link rel="stylesheet" href="css/style_login.css"/>
           <link rel="stylesheet" href="assets/css/main.css" />


	</head>

    <style>



li.icons{
    float: left;
}


li.icons a {
    color:black;
    display: block;
    text-align: center;
    padding: 22px 26px;

    text-decoration: none;
}


/* Change the link color to #111 (black) on hover */
/*drop down bar*/

li.icons a :hover {
    background-color: #111;
}

.active {
    background-color: #4CAF50;
}

.loginField
        {
            color: grey;
        }


    </style>

    <body>
<!-- NavBar new -->
   <div class="w3-top topNavBar">

  <div class="w3-bar w3-black" id="myNavbar">

    <a class="w3-bar-item w3-button w3-hover-black  w3-hide-large w3-left" href="javascript:void(0);" onclick="toggleFunction()" title="Toggle Navigation Menu">
      <i class="fa fa-bars"></i>
    </a>

    <a href="index.html" class="w3-bar-item w3-button w3-hide-small w3-hide-medium navbar w3-padding-large myTab">Home</a>
    <a href="tables.html" class="w3-bar-item w3-button w3-hide-small w3-hide-medium navbar w3-padding-large myTab"> Data</a>
    <a href="contact.html" class="w3-bar-item w3-button w3-hide-small w3-hide-medium navbar myTab w3-padding-large" > Contact</a>
    <a href="about.html" class="w3-bar-item w3-button w3-hide-small w3-hide-medium w3-padding-large navbar myTab"> About</a>
    <a href="login.html" class = "w3-bar-item w3-button w3-hide-small w3-hide-medium w3-padding-large navbar myTab active"> Log In </a>

  </div>


   <!-- Navbar on small screens -->
  <div id="navDemo" class="w3-bar-block w3-mobile w3-black w3-hide w3-hide-large">
    <a href="index.html" class="w3-bar-item w3-button" onclick="toggleFunction()">Home</a>
    <a href="tables.html" class="w3-bar-item w3-button" onclick="toggleFunction()">Data</a>
    <a href="contact.html" class="w3-bar-item w3-button" onclick="toggleFunction()">Contact</a>
    <a href="about.html" class="w3-bar-item w3-button" onclick="toggleFunction()">About</a>
    <a href="login.html" class="w3-bar-item w3-button" onclick="toggleFunction()">Log In</a>
  </div>


</div>

    <!--- issue with formatting text to be in center mid screen level--->

        <div class="form">

      <ul class="tab-group">
        <li class="tab active"><a href="#signup">Sign Up</a></li>
        <li class="tab"><a href="#login">Log In</a></li>
      </ul>

      <div class="tab-content">
        <div id="signup">
          <h1>Sign Up for Free</h1>

          <form action="includes/signup.inc.php" method="post">

          <div class="top-row">
            <div class="field-wrap">
              <label class="loginField">
                First Name<span class="req">*</span>
              </label>
              <input type="text" name="first" required autocomplete="off" />
            </div>

            <div class="field-wrap">
              <label class="loginField">
                Last Name<span class="req">*</span>
              </label>
              <input type="text" name="last" required autocomplete="off"/>
            </div>
          </div>

		  <div class="field-wrap">
			<label class="loginField">
			  Email Address<span class="req">*</span>
			</label>
			<input type="email" name="email"required autocomplete="off"/>
		  </div>

          <div class="field-wrap">
            <label class="loginField">
              Username<span class="req">*</span>
            </label>
            <input type="text" name="uid"required autocomplete="off"/>
          </div>

          <div class="field-wrap">
            <label class="loginField">
              Set A Password<span class="req">*</span>
            </label>
            <input type="password" name = "pwd" required autocomplete="off"/>
          </div>

          <button type="submit" name="submit" class="button button-block">Get Started</button>

          </form>

        </div>

        <div id="login">
          <h1>Welcome Back!</h1>

          <form action="/" method="post">

            <div class="field-wrap">
            <label class="loginField">
              Email Address<span class="req">*</span>
            </label>
            <input type="email"required autocomplete="off"/>
          </div>

          <div class="field-wrap">
            <label class="loginField">
              Password<span class="req">*</span>
            </label>
            <input type="password"required autocomplete="off"/>
          </div>

          <p class="forgot"><a href="#">Forgot Password?</a></p>

          <button class="button button-block">Log In</button>

          </form>

        </div>

      </div><!-- tab-content -->

</div> <!-- /form -->


    </body>

     <!-- Footer -->
					<footer class="wrapper style1 align-center">
						<div class="inner">
							<ul class="icons" style = "display: inline-block;">
								<li class = "icons"><a href="#" class="icon style2 fa-twitter"><span class="label">Twitter</span></a></li>
								<li class = "icons"><a href="#" class="icon style2 fa-facebook"><span class="label">Facebook</span></a></li>
								<li class = "icons"><a href="#" class="icon style2 fa-instagram"><span class="label">Instagram</span></a></li>
								<li class = "icons"><a href="#" class="icon style2 fa-linkedin"><span class="label">LinkedIn</span></a></li>
								<li class = "icons"><a href="#" class="icon style2 fa-envelope"><span class="label">Email</span></a></li>
							</ul>
							<p>&copy; iPlant 2017. Design: <a href="https://html5up.net">HTML5 UP</a>.</p>
						</div>
					</footer>



		<!-- Scripts -->
			<script src="assets/js/jquery.min.js"></script>
			<script src="assets/js/jquery.scrollex.min.js"></script>
			<script src="assets/js/jquery.scrolly.min.js"></script>
			<script src="assets/js/skel.min.js"></script>
			<script src="assets/js/util.js"></script>
			<script src="assets/js/main.js"></script>
    
                    <script>
// NEW drop down menu
    function toggleFunction() {
    var x = document.getElementById("navDemo");
    if (x.className.indexOf("w3-show") == -1) {
        x.className += " w3-show";
    } else {
        x.className = x.className.replace(" w3-show", "");
    }
}
</script>
			

        <script src='http://cdnjs.cloudflare.com/ajax/libs/jquery/2.1.3/jquery.min.js'></script>
    <script src="http://ajax.googleapis.com/ajax/libs/jquery/2.0.0/jquery.min.js"></script>


    <script src="http://code.jquery.com/jquery-2.2.4.min.js"></script>
    <script src="js/index_login.js"></script>


</html>
