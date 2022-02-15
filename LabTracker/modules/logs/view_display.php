<?php
	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/5/2018 10:53
	 */
?>
<!doctype html>
<html lang="en">
<head>

	<?php include CORE_PATH . 'assets/inc/meta.php'; ?>
	<?php Core::includeStyles(); ?>
</head>
<body id="<?= $data['_id']?>">
<?php
	include CORE_PATH . 'assets/inc/header.php';
	include CORE_PATH . 'assets/inc/nav.php';
?>
<section id="main">
	<h1>Error Log</h1>
	<div>
	<label>Refresh Interval</label>
	<input name="interval" type="number" value="5" placeholder="Seconds">
	<input name="refresh" type="button" value="Refresh Now">
	<input name="stop" type="button" value="Stop Refreshing">

	<a href="<?= CORE_URL ?>logs/clear">
		<input name="clear" type="button" value="Clear Log">
	</a>
	</div>
	<div class="logs margin15Top">
		<?php
			$GLOBALS['main']->logs->refresh();
		?>
	</div>
</section>
<?php include( CORE_PATH . 'assets/inc/footer.php' ); ?>
</body>
</html>
