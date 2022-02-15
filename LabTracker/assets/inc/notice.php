<?php
	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 1/7/2019 16:10
	 */
	$minimized = isset( $_COOKIE['noticeMinimize'] ) ? $_COOKIE['noticeMinimize'] : false;
	if( MAINTENANCE ){
	?>
<div class="systemNotice error <?= $minimized ? 'minimized' : ''?>">
	<div id="warning">
		<div class="flex notice">
			<strong><i class="fas fa-exclamation-circle"></i>&nbsp;Site is undergoing maintenance.&nbsp;</strong>
			<p>Some features may not work correctly.</p>
		</div>
		<div>
			<input type="button" class="noticeDismiss" value="Minimize" />
		</div>
	</div>
</div>
<?php }
	if( SERVER_MAINTENANCE ){
		?>
		<div class="systemNotice error <?= $minimized ? 'minimized' : ''?>">
			<div id="warning">
				<div class="flex notice">
					<strong><i class="fas fa-exclamation-circle"></i>&nbsp;Servers are undergoing maintenance.&nbsp;</strong>
					<p>Code running has been impacted and may not run or run slower than usual</p>
				</div>
				<div>
					<input type="button" class="noticeDismiss" value="Minimize" />
				</div>
			</div>
		</div>
<?php }
	if( NOTICE ){
	?>
	<div class="systemNotice notice <?= $minimized ? 'minimized' : ''?>">
		<div id="warning">
			<div class="flex notice">
				<strong><i class="fas fa-exclamation-triangle"></i>&nbsp;Notice.&nbsp;</strong>
				<p><?= NOTICE_MESSAGE ?></p>
			</div>
			<div>
				<input type="button" class="low noticeDismiss" value="Minimize" />
			</div>
		</div>
	</div>
<?php }
	if( ERROR ){
		?>
		<div class="systemNotice error <?= $minimized ? 'minimized' : ''?>">
			<div id="warning">
				<div class="flex notice">
					<strong><i class="fas fa-exclamation-circle"></i>&nbsp;Error.&nbsp;</strong>
					<p><?= ERROR_MESSAGE ?></p>
				</div>
				<div>
					<input type="button" class="low noticeDismiss" value="Minimize" />
				</div>
			</div>
		</div>
	<?php }