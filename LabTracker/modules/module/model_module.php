<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/4/2018 20:42
	 */
	class model_module {
		protected $moduleName;

		public function __construct( App $app, $name ) {
			$this->app = $app;
			$this->moduleName = $name;
		}

		/**
 		 * get a single record from the database
		 * @param array $options
		 * {
		 * "where": "",
		 * "params": [],
		 * "order": "",
		 * "fields": "*",
		 * "table": "$this->moduleName",
		 * "query": ""
		 * }
		 * @return array|bool if found returns record else returns false
		 */
		function getOne( $options = array() ) {
			$options = Core::getOptions( array(
				'where' => '',
				'params' => array(),
				'order' => '',
				'fields' => '*',
				'table' => $this->moduleName,
				'query' => ''
			), $options );
			$items = array();
			if ( !empty( $options['query'] ) ) {
				if ( !empty( $options['where'] ) ) {
					$state = $this->app->db->prepare( "${options['query']} WHERE ${options['where']}" );
				} else {
					$state = $this->app->db->prepare( "${options['query']}" );
				}
				if ( $state === false ) {
					$this->app->lastError = $this->app->db->error;
					$this->app->logs->error( $this->app->db->error, logs::MYSQL_FATAL, Debug::callStack() );
					return false;
				}
				if ( !empty( $options['params'] ) ) {
					$params = array( '' );
					foreach ( $options['params'] as $i => &$val ) {
						$params[0] .= DbHelper::getTypeMysql( $val );
						$params[$i + 1] = &$val;
					}
					//call $state->bind_params() with this because unknown amount of params
					call_user_func_array( array( $state, 'bind_param' ), $params );
				}
			} else if ( !empty( $options['where'] ) && !empty( $options['params'] ) ) {
				if ( !empty( $options['order'] ) ) {
					$state = $this->app->db->prepare( "SELECT ${options['fields']} FROM ${options['table']} WHERE ${options['where']} ORDER BY ${options['sort']}" );
				} else {
					$state = $this->app->db->prepare( "SELECT ${options['fields']} FROM ${options['table']} WHERE ${options['where']}" );
				}
//				echo "SELECT ${options['fields']} FROM ${options['table']} WHERE ${options['where']}";
				if ( $state === false ) {
					$this->app->lastError = $this->app->db->error;
					$this->app->logs->error( $this->app->db->error, logs::MYSQL_FATAL, Debug::callStack() );
					return false;
				}
				$params = array( '' );
				foreach ( $options['params'] as $i => &$val ) {
					$params[0] .= DbHelper::getTypeMysql( $val );
					$params[$i + 1] = &$val;
				}
				//call $state->bind_params() with this because unknown amount of params
				call_user_func_array( array( $state, 'bind_param' ), $params );
			} else {
				if ( !empty( $options['order'] ) )
					$state = $this->app->db->prepare( "SELECT ${options['fields']} FROM ${options['table']} ORDER BY ${options['sort']}" );
				else
					$state = $this->app->db->prepare( "SELECT ${options['fields']} FROM ${options['table']}" );
				if ( $state === false ) {
					$this->app->lastError = $this->app->db->error;
					$this->app->logs->error( $this->app->db->error, logs::MYSQL_FATAL, Debug::callStack() );
					return false;
				}
			}

			if ( $state->execute() ) {
				$result = $state->get_result();
				$items = $result->fetch_assoc();
			} else {
				$this->app->lastError = $state->error;
				$this->app->logs->error( $state->error, logs::MYSQL_ERROR, Debug::callStack() );
				return false;
			}

			if( $items === null )
                $items = false;
			return $items;
		}

		/**
		 * Gets items from the database
		 * format for the options array as follows
		 * {
		 *	 where: 'field=?,field2=?',
		 *	 params: [ 4, 'LIKE str'],
		 *	 order: 'column DESC',
		 *	 fields: 'id,name,field',
		 *	 table: 'moduleName',
		 *	 limit: 'offset,limit',
		 *	 query: 'an entire query to join if easier'
	 	* }
		 * @param array $options
		 * @return array|bool
		 */
		function get( $options = array() ) {
			$options = Core::getOptions( array(
				'where' => '',
				'params' => '',
				'order' => '',
				'fields' => '*',
				'table' => $this->moduleName,
				'limit' => '',
				'query' => ''
			), $options );
			$items = array();
			$QUERY = "";
			//if query is inputted
			if ( !empty( $options['query'] ) ) {
				$QUERY = "${options['query']}";
				if ( !empty( $options['where'] ) ) {
					$QUERY = "${options['query']} WHERE ${options['where']}";
					if( !empty( $options['limit'] ) ){
						$QUERY .= " LIMIT ${options['limit']}";
					}
				} else {
				}
				$state = $this->app->db->prepare( $QUERY );
				if ( $state === false ) {
					$this->app->lastError = $this->app->db->error;
					$this->app->logs->error( $this->app->db->error, logs::MYSQL_FATAL, Debug::callStack() );
					return false;
				}
				if ( !empty( $options['params'] ) ) {
					$params = array( '' );
					foreach ( $options['params'] as $i => &$val ) {
						$params[0] .= DbHelper::getTypeMysql( $val );
						$params[$i + 1] = &$val;
					}
					//call $state->bind_params() with this because unknown amount of params
					call_user_func_array( array( $state, 'bind_param' ), $params );
				}
			} else if ( !empty( $options['where'] ) && !empty( $options['params'] ) ) {
				$QUERY = "SELECT ${options['fields']} FROM ${options['table']} WHERE ${options['where']}";
				if ( !empty( $options['order'] ) ) {
					$QUERY .= " ORDER BY ${options['order']}";
				}
				if( !empty( $options['limit'] ) ){
					$QUERY = "SELECT SQL_CALC_FOUND_ROWS ${options['fields']} FROM ${options['table']} WHERE ${options['where']}";
					if ( !empty( $options['order'] ) ) {
						$QUERY .= " ORDER BY ${options['order']}";
					}
					$QUERY .= " LIMIT ${options['limit']}";
				}

				$state = $this->app->db->prepare( $QUERY );

				if ( $state === false ) {
					$this->app->lastError = $this->app->db->error;
					$this->app->logs->error( $this->app->db->error, logs::MYSQL_FATAL, Debug::callStack() );
					return false;
				}
				$params = array( '' );
				foreach ( $options['params'] as $i => &$val ) {
					$params[0] .= DbHelper::getTypeMysql( $val );
					$params[$i + 1] = &$val;
				}
				//call $state->bind_params() with this because unknown amount of params
				call_user_func_array( array( $state, 'bind_param' ), $params );
			} else {
				if( !empty( $options['limit'] ) ){
					$QUERY = "SELECT SQL_CALC_FOUND_ROWS ${options['fields']} FROM ${options['table']}";
					if ( !empty( $options['order'] ) ) {
						$QUERY .= " ORDER BY ${options['order']}";
					}
					$QUERY .= " LIMIT ${options['limit']}";
					$state = $this->app->db->prepare( $QUERY );
				} else if ( !empty( $options['order'] ) )
					$state = $this->app->db->prepare( "SELECT ${options['fields']} FROM ${options['table']} ORDER BY ${options['order']}" );
				else
					$state = $this->app->db->prepare( "SELECT ${options['fields']} FROM ${options['table']}" );
				if ( $state === false ) {
					$this->app->lastError = $this->app->db->error;
					$this->app->logs->error( $this->app->db->error, logs::MYSQL_FATAL, Debug::callStack() );
					return false;
				}
			}

			if ( $state->execute() ) {
				$result = $state->get_result();
				while ( ( $row = $result->fetch_assoc() ) != null ) {
					array_push( $items, $row );
				}
			} else {
				$this->app->lastError = $state->error;
				$this->app->logs->error( $state->error, logs::MYSQL_ERROR, Debug::callStack() );
				return false;
			}

			if( !empty( $options['limit'] ) ){
				//get the found pages
				$count = $this->app->db->query( "SELECT FOUND_ROWS()" );
				$total = $count->fetch_row()[0];
				$pageBreakdown = explode( ",", $options['limit'] );

				$result  = [
					'items' => $items,
					'pagination' => [
						'count' => $total,
						'limit' => (int) $pageBreakdown[0],
					]
				];
				if( count( $pageBreakdown ) > 1 ){
					$result['pagination']['page'] = ( ( (int)$pageBreakdown[0] > 0 ) ? ( (int) $pageBreakdown[0] / (int) $pageBreakdown[1] ) : ( 0 ) );
					$result['pagination']['limit'] = (int) $pageBreakdown[1];
					$result['pagination']['more'] = ($result['pagination']['page'] + 1) * $result['pagination']['limit'] < $total;
				}
				return $result;
			}
			return $items;
		}

		/**
		 * update a course in the database
		 * @param array $options
		 * {
		 * id: id
		 * where: 'field=?,f2=?',
		 * update: 'field3=?',
		 * params: [ update, where ],
		 * table: 'table'
		 * @return bool
		 */
		function update( $options = array() ) {
			$options = Core::getOptions( array(
				'id' => -1,
				'where' => '',
				'update' => '',
				'params' => array(),
				'table' => $this->moduleName,
				'query' => '' //"UPDATE ${options['table']} SET ${options['update']} WHERE id=?"
			), $options );
			if( $options['id'] != -1 && empty( $options['where'] ) ){
				$options['where'] = 'id=?';
				array_push( $options['params'], $options['id'] );
			}

			$QUERY = '';

			if( !empty( $options['query'] ) ){
				$QUERY = $options['query'];
				$state = $this->app->db->prepare( $QUERY );
			} else if( !empty( ['update'] ) && !empty( $options['params'] ) ) {
				$QUERY = "UPDATE ${options['table']} SET ${options['update']} WHERE ${options['where']}";
				$state = $this->app->db->prepare( $QUERY );
			} else{
				$this->app->logs->error( "Not enough data to complete update", logs::MYSQL_FATAL, Debug::callStack() );
				return false;
			}

			if ( $state === false ) {
				$this->app->lastError = $this->app->db->error;
				$this->app->logs->error( $this->app->db->error, logs::MYSQL_FATAL, Debug::callStack() );
				return false;
			} else {
				//bind params
				$params = array( '' );
				foreach ( $options['params'] as $i => &$val ) {
					$params[0] .= DbHelper::getTypeMysql( $val );
					$params[$i + 1] = &$val;
				}

				//call $state->bind_params() with this because unknown amount of params
				call_user_func_array( array( $state, 'bind_param' ), $params );

				if ( $state->execute() ) {
					return true;
				} else {
					$this->app->lastError = $state->error;
					$this->app->logs->error( $state->error, logs::MYSQL_ERROR, Debug::callStack() );
					return false;
				}
			}
		}

		/**
		 * @param array $options
		 * { 'fields' => 'field1,field2',
		 *   'params' => array( val1, val2 ),
		 *   'table' => 'table'
		 *   'query' => 'sql query to run' }
		 * @return bool|int
		 */
		public function insertOne( $options = array() ) {
			//have to have this cause cant default options like below for this
			$options['table'] = isset( $options['table'] ) ? $options['table'] : $this->moduleName;
			$hasQuery = isset( $options['query'] );
			$options = Core::getOptions( array(
				'fields' => '',
				'params' => array(),
				'table' => $this->moduleName,
				'query' => "INSERT INTO ${options['table']}(${options['fields']}) VALUES("
			), $options );

			if ( !empty( $options['fields'] ) && !empty( $options['params'] ) ) {
				//count the fields
				if ( !$hasQuery ) {
					$len = count( explode( ',', $options['fields'] ) );
					$vals = '';
					for ( $i = 0; $i < $len; $i++ ) {
						$vals .= '?';
						if ( $i + 1 != $len ) {
							$vals .= ',';
						}
					}
					$options['query'] .= $vals . ')';
				}

				$state = $this->app->db->prepare( $options['query'] );
				if ( $state === false ) {
					$this->app->lastError = $this->app->db->error;
					$this->app->logs->error( $this->app->db->error, logs::MYSQL_FATAL, Debug::callStack() );
					return false;
				}
				//bind params
				$params = array( '' );
				foreach ( $options['params'] as $i => &$val ) {
					$params[0] .= DbHelper::getTypeMysql( $val );
					$params[$i + 1] = &$val;
				}
				//call $state->bind_params() with this because unknown amount of params
				call_user_func_array( array( $state, 'bind_param' ), $params );
				if ( $state->execute() ) {
					return $state->insert_id;
				} else {
					$this->app->lastError = $state->error;
					$this->app->logs->error( $state->error, logs::MYSQL_ERROR, Debug::callStack() );
					return false;
				}
			}
		}

		/**
		 * @param array $options
		 * {
		 * [id: int],
		 * where: 'field=?',
		 * params: [ val ],
		 * table: tableName,
		 * query: 'fullQuery'
		 * }
		 * @return bool
		 */
		public function delete( $options = array() ){
			$options = Core::getOptions( array(
				'id' => -1,
				'where' => '',
				'params' => array(),
				'table' => $this->moduleName,
				'query' => '' //"UPDATE ${options['table']} SET ${options['update']} WHERE id=?"
			), $options );

			if( $options['id'] != -1 && empty( $options['where'] ) ){
				$options['where'] = 'id=?';
				array_push( $options['params'], $options['id'] );
			}

			if( !empty( $options['query'] ) ){
				$state = $this->app->db->prepare( $options['query'] );
			} else if( !empty( $options['where'] ) && !empty( $options['params'] ) ) {
				$state = $this->app->db->prepare( "DELETE FROM ${options['table']} WHERE ${options['where']}" );
			}else{
				$this->app->logs->error( "Not enough data to complete delete", logs::MYSQL_FATAL, Debug::callStack() );
				return false;
			}

			if ( $state === false ) {
				$this->app->lastError = $this->app->db->error;
				$this->app->logs->error( $this->app->db->error, logs::MYSQL_FATAL, Debug::callStack() );
				return false;
			} else {
				//bind params
				$params = array( '' );
				foreach ( $options['params'] as $i => &$val ) {
					$params[0] .= DbHelper::getTypeMysql( $val );
					$params[$i + 1] = &$val;
				}

				//call $state->bind_params() with this because unknown amount of params
				call_user_func_array( array( $state, 'bind_param' ), $params );

				if ( $state->execute() ) {
					return true;
				} else {
					$this->app->lastError = $state->error;
					$this->app->logs->error( $state->error, logs::MYSQL_ERROR, Debug::callStack() );
					return false;
				}
			}
		}

		/**
		 * mark a row as deleted by changing the active to to false instead of deleting it
		 * no option['query'] allowed
		 * @param array $options
		 * {
		 * [id: int],
		 * where: 'field=?',
		 * params: [ val ],
		 * table: tableName,
		 * }
		 * @return bool
		 */
		public function markDeleted( $options = array() ){
			$options = Core::getOptions( array(
				'id' => -1,
				'where' => '',
				'params' => array(),
				'table' => $this->moduleName,
				'delete' => 0,
				'query' => '' //"UPDATE ${options['table']} SET ${options['update']} WHERE id=?"
			), $options );

			if( $options['id'] != -1 && empty( $options['where'] ) ){
				$options['where'] = 'id=?';
				array_push( $options['params'], $options['id'] );
			}

			if( is_numeric( $options['delete'] ) ){
				$options['delete'] = intval( $options['delete'] );
			} else {
				$this->app->logs->error( "options['delete'] was not an integer", logs::MYSQL_FATAL, Debug::callStack() );
				return false;
			}

			if( !empty( $options['where'] ) && !empty( $options['params'] ) ) {
				$state = $this->app->db->prepare( "UPDATE ${options['table']} SET active=${options['delete']} WHERE ${options['where']}" );
			}else{
				$this->app->logs->error( "Not enough data to complete update", logs::MYSQL_FATAL, Debug::callStack() );
				return false;
			}

			if ( $state === false ) {
				$this->app->lastError = $this->app->db->error;
				$this->app->logs->error( $this->app->db->error, logs::MYSQL_FATAL, Debug::callStack() );
				return false;
			} else {
				//bind params
				$params = array( '' );
				foreach ( $options['params'] as $i => &$val ) {
					$params[0] .= DbHelper::getTypeMysql( $val );
					$params[$i + 1] = &$val;
				}

				//call $state->bind_params() with this because unknown amount of params
				call_user_func_array( array( $state, 'bind_param' ), $params );

				if ( $state->execute() ) {
					return true;
				} else {
					$this->app->lastError = $state->error;
					$this->app->logs->error( $state->error, logs::MYSQL_ERROR, Debug::callStack() );
					return false;
				}
			}
		}
	}
