<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 4/5/2018 12:01
	 */
	class logs extends module {
		const PHP_WARNING = 0;
		const PHP_ERROR = 1;
		const PHP_FATAL = 2;
		const MYSQL_WARNING = 3;
		const MYSQL_ERROR = 4;
		const MYSQL_FATAL = 5;
		const ERROR = 6;
		const PHP_DEPRECATED = 7;
		const PHP_NOTICE = 8;
		const INFO = 9;

		public function fetch( $options = array() ) {
			// TODO: Implement fetch() method.
		}

        public function fetchOne( $options = array() ) {
            // TODO: Implement fetchOne() method.
        }

		public function error( $error, $level = self::PHP_WARNING, $source = '', $user = -1 ) {
			if ( $user == -1 && isset( $_SESSION['session']['id'] ) ) {
				$user = $_SESSION['session']['id'];
			}
			$this->model->insertOne( array(
				'fields' => 'error,source,level,user,date',
				'params' => array(
					$error,
					$source,
					$level,
					$user,
					DbHelper::now()
				)
			) );
		}

		public function display() {
			if ( $this->app->users->loggedInOrRedirect( 'logs/display' ) ) {
				if ( $_SESSION['session']['role'] == users::DEBUGGER ) {
					$this->app->loadView( $this->moduleName, 'display' );
				} else {
					$this->app->throwError( 404 );
				}
			}
		}

		public function nodes(){
			if( $this->app->users->orRedir( 'logs/nodes' ) ){
				if( $_SESSION['session']['role'] == users::DEBUGGER ){
					$this->app->loadView( $this->moduleName, 'nodes' );
				} else {
					$this->app->throwError( 404 );
				}
			}
		}

		public function session(){
			//todo private this for live
			if( Core::getRole() >= users::DEBUGGER ) {
				$this->app->loadPage( 'basic-template', [ 'data' => '<h1>Session Data</h1>' . Debug::simpleJson( $_SESSION, true ) ] );
			} else
				$this->app->throwError( 404 );
//			Debug::println( $_SESSION );
		}

		public function clear(){
			if ( $_SESSION['session']['role'] == users::DEBUGGER ) {
				$this->model->truncate();
				Core::phpRedirect( 'logs/display');
			}
		}

		public function refresh() {
			$logs = $this->model->get( array(
				'table' => 'logs',
				'order' => 'id desc'
			) );
			echo '<table>';
			foreach ( $logs as $item ) {
				echo '<tr>';
				echo '<td>';
				echo Logs::levelToText( $item['level'] );
				echo '</td>';
				echo '<td>';
				echo $item['error'];
				echo '</td>';
				echo '<td><pre>';
				echo $item['source'];
				echo '</pre></td>';
				echo '<td>';
				echo Date( "n/j/y G:i", strtotime( $item['date'] ) );
				echo '</tr>';
				echo '</tr>';
			}
			echo '</table>';
		}

		public function refreshNodes(){
			$nodes = $this->model->get( [
				'table' => 'nodes',
				'order' => 'state ASC'
			] );
//			Debug::println( $nodes );
			?>
			<table class="width100">
				<thead>
					<tr>
						<th>UUID</th>
						<th>IP</th>
						<th>State</th>
					</tr>
				</thead>
				</tbody>
			<?php
			foreach ( $nodes as $item ) {
				echo '<tr>';
				echo '<td>';
				echo $item['uuid'];
				echo '</td>';
				echo '<td>';
				echo $item['ip'] . ':' . $item['port'];
				echo '</td>';
				echo '<td>';
				if ( $item['state'] == 0 )
					echo '<span class="green">Available</span>';
				else if( $item['state'] == 1 )
					echo '<span class="yellow">Busy</span>';
				else if( $item['state'] == 50 )
					echo '<span class="red">Removed/Duplicate Down</span>';
				else
					echo '<span class="red">Down</span>';
				echo '</td>';
				echo '</tr>';
			}
			?>
				</tbody>
			</table>
			<?php
		}

		public static function levelToText( $val ) {
			switch ( $val ) {
				case self::PHP_WARNING :
					return 'PHP Warning';
				case self::PHP_ERROR :
					return 'PHP Error';
				case self::PHP_FATAL:
					return 'PHP Fatal';
				case self::MYSQL_WARNING:
					return 'MySQL Warning';
				case self::MYSQL_ERROR :
					return 'MySQL Error';
				case self::MYSQL_FATAL :
					return 'MySQL Fatal';
				case self::ERROR :
					return 'Error';
				case self::PHP_DEPRECATED:
					return 'PHP Deprecated';
				case self::PHP_NOTICE:
					return 'PHP Notice';
				case self::INFO:
					return 'Info';
			}
		}


    }