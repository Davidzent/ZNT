<?php
	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 3/6/2018 13:01
	 */
?>
<?php
$cprefs = true; //isset( $_COOKIE['cprefs'] ) ? true : false;
if( !$cprefs ) {
?>
<div class="consentWrapper">
	<div>
		<p>We use cookies to offer you a better experience and analyze site traffic. By continuing to use this website, you consent to the use of cookies in accordance with out Cookie Policy</p>
		<div>
			<input class="flat" type="button" value="Accept" id="consentApprove" />
			<input class="flat" type="button" value="Preferences" id="consentPref" />
		</div>
	</div>
</div>
<?php } ?>
<footer>
	<ul class="footerMenu">
		<li><a href="<?=CORE_URL?>home">Home</a></li>
		<li><a href="<?=CORE_URL?>help">Help</a></li>
		<li><a href="<?=CORE_URL?>credits">Libraries</a></li>
	</ul>
    <div class="bestUsed">
        For best results using the Lab Tracker use <a href="https://www.google.com/chrome/"><i class="fab fa-chrome"></i>Google Chrome<i class="far fa-copyright"></i></a>
    </div>
	<ul class="footerMenu">
		<li><?= Core::copyright()?></li>
	</ul>
</footer>
<?php Core::includeScripts() ?>