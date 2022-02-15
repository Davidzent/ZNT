<?php
	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/21/2018 18:56
	 */

	$links = array(
		[
			'url' => 'home',
			'text' => 'Home',
			'role' => users::NOT_SIGNED_IN,
		],
		[
			'url' => 'courses',
			'text' => 'Courses',
			'role' => users::NOT_SIGNED_IN,
			'dropdown' => [
				[
					'url' => 'courses',
					'text' => 'My Courses',
					'role' => users::NOT_SIGNED_IN,
				],
				[
					'url' => 'courses/create',
					'text' => 'Create Course',
					'role' => users::TEACHER,
				],
				[
					'url' => 'courses/listing',
					'text' => 'Course Listings',
					'role' => users::ADMIN,
				]
			]
		],
		[
			'text' => 'Questions',
			'dropdown' => [
				[
					'url' => 'questions/listing',
					'text' => 'Questions',
					'role' => users::AIDE
				],
				[
					'url' => 'questions/create',
					'text' => 'Create Question',
					'role' => users::AIDE
				],
				[
					'url' => 'questions/import',
					'text' => 'Import Question',
					'role' => users::TEACHER
				]
			]
		],
		[
			'text' => 'Admin',
			'role' => -1,
			'dropdown' => [
				[
					'url' => 'users/listing',
					'text' => 'Users',
					'role' => users::ADMIN
				],
				[
					'text' => 'Debug',
					'dropdown' => [
						[
							'url' => 'logs/display',
							'text' => 'Error Logs',
							'role' => users::DEBUGGER
						],
						[
							'url' => 'logs/nodes',
							'text' => 'Node Status',
							'role' => users::DEBUGGER
						],
						[
							'url' => 'logs/session',
							'text' => 'Session details',
							'role' => users::DEBUGGER
						],
					]
				],
				[
					'text' => 'Feedback',
					'role' => users::ADMIN,
					'dropdown' => [
						[
							'text' => 'Listing',
							'url' => 'feedback/listing',
							'role' => users::ADMIN
						],
					]
				],
				[ 'url' => 'https://webmail.tierra.net/', 'text' => 'WebEmail', 'role' => users::DEBUGGER ]
			]
		],
		[
			'text' => 'Feedback / Bugs',
			'role' => users::GUEST,
			'hide' => users::ADMIN,
			'url' => 'feedback/report'
		],
	);

	$GLOBALS['app']->loadModules( 'users notifications' );
	function linkStr( $link ){
		//if should hide the link do so
		$role = Core::getRole();
		if( isset( $link['hide'] ) && $link['hide'] <= $role ) //Core::getRole()
			return false;
		if ( $role >= $link['role'] ) { //if can access this link print it
			$url = '#';
			if ( isset( $link['url'] ) ) {
				if( preg_match( '/^https?:\/\/.+?$/', $link['url'] ) ){
					$url = $link['url'];
				} else {
					$url = CORE_URL . $link['url'];
				}
			}
			$s = "<li>";
			$s .= "<a href='" . $url . "'>" . $link['text'] . "</a></li>";
			return $s;
		}
		return false;
	}

	function printLis( $link ){
		if ( isset( $link['dropdown'] ) ) {
			$count = 0;
			$str  = '<li class="dropdown">';
			$str .= '<a>' . $link['text'] . '&nbsp;<i class="fas fa-chevron-down" aria-hidden="true"></i></a>';
			$str .= '<ul>';
			$ulStr = '';
			foreach ( $link['dropdown'] as $item ) {
				if( isset( $item['dropdown'] ) ){
					$temp = printLis( $item );
					if( !empty( $temp ) ) {
						$count++;
						$ulStr .= $temp;
					}
				} else {
					$temp = linkStr( $item );
					if( $temp !== false ) {
						$count++;
						$ulStr .= $temp;
					}
				}

			}
			if ( isset( $link['url'] ) ) {
				if( $count > 1 ) { //then it is a list and we can just print it
					$str .= $ulStr . '</ul></li>';
					return $str;
				} else {
					return $ulStr;
				}
			} else {
				if( $count >= 1 ) { //then it is a list and we can just print it
					$str .= $ulStr . '</ul></li>';
					return $str;
				}
			}
		} else{
			return linkStr( $link );
		}
	}
?>
<nav>
	<div class="menu clearfix">
		<ul>
			<?php
				foreach ( $links as $link ) {
					echo printLis( $link );
				}
			$links = null;

				//if have active course
				if( isset( $_SESSION['activeCourse'] ) ){
					$temp = '/' . CORE_DIR . 'courses/' . $_SESSION['activeCourse'];
					echo "<li>";
					echo "<a href='" . CORE_URL . "courses/" . $_SESSION['activeCourse'] . "'>To Course</a></li>";
				}

				if( !$GLOBALS['app']->users->isLoggedIn() ) {
					echo '<li class="floatright">';
					$ref = isset( $_SERVER['REDIRECT_URL'] ) ? $_SERVER['REDIRECT_URL'] : '';
					$ref = str_replace( CORE_DIR, '', $ref );
					$ref= '?ref=' . $ref;
					echo "<a href='" . CORE_URL . "users/login$ref'>Login</a>";
					echo '</li>';
				} else {
					?>
			<li class='floatright dropdown'>
				<a><?= $GLOBALS['app']->users->getRoleIcon()?>&nbsp;<?=$_SESSION['session']['name']?>&nbsp;<i class='fas fa-chevron-down' aria-hidden='true'></i></a>
				<ul class="dropdownContent">
					<li><a href="<?=CORE_URL ?>users/profile">Edit Profile</a></li>
					<li><a href="<?=CORE_URL ?>users/logout">Logout</a> </li>
				</ul>
			</li>
			<li class="floatright noticesWrapper">
				<a class="tooltip relative" title="Notifications">
					<i class="far fa-bell" aria-hidden="true"></i>
					<span class="noticeNumber<?= ( ( $GLOBALS['app']->notifications->hasNotices() ) ? ( '' ) : ( ' none' ) );?>">&nbsp;</span>
				</a>
				<div class="notices">
					<?php
						$GLOBALS['app']->notifications->getNotificationMenu();
					?>
				</div>
			</li>
			<?php
				}
			?>
			<li class="floatright">
				<a class="tooltip <?= isset( $_SESSION['dark'] ) && $_SESSION['dark'] ? 'rotate180 ' : '' ?>" title="<?= isset( $_SESSION['dark'] ) && $_SESSION['dark'] ? 'Turn on ' : 'Turn off ' ?>the lights" href="<?=CORE_URL?>pages/invert">
					<i class="fas fa-adjust" aria-hidden="true"></i>
				</a>
			</li>

		</ul>
	</div>
</nav>
