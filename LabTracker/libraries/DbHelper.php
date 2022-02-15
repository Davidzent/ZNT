<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/4/2018 19:21
	 */
	class DbHelper {
		public function __construct( App $app ) {
			$this->app = $app;
		}

		/**
		 * returns the first record or a false if not found
		 * @param string $sql mysql query
		 * @return array|bool array of result or false if not found
		 */
		public function getOne( $sql ) {
			$result = $this->app->db->query( $sql );
			$row = $result->fetch_assoc();

			if ( $row ) {
				return $row;
			} else {
				return false;
			}
		}

		/**
		 * get right now in a datetime
		 * @return bool|string
		 */
		public static function now(){
			return date("Y-m-d H:i:s");
		}

		/**
		 * turns a string into the right format for mysql
		 * @param $str
		 * @return bool|string
		 */
		public static function datetimeStr( $str ){
			return date( 'Y-m-d H:i:s', strtotime( $str ) );
		}

		/**
		 * @param $table
		 * @param $where
		 * @param array $data
		 * @return bool true if successful
		 * {
		 * id : data,  //required
		 * column : data
		 * }
		 */
		public function upsertRecord( $table, $where, $data = array() ){
			$exists = false;
			if( isset( $where ) ) {
				$query = "SELECT * FROM $table WHERE $where";
				if( !$result = @$this->db->query($query) ){
					return false;
				}
				if( @$result->num_rows > 0 ){
					$exists = true;
				}
				@$result->close();
				$evalStr = "\$state->bind_param(";
				$bindType = '';
				$paramsStr = '';
				if ( $exists ) { //exists so update
					$query = "UPDATE $table SET ";
					foreach( $data as $key => $val ){
						$query .= $key . '=?,';
						$paramsStr .= "\$data['$key'], ";
						$bindType .= $this->getTypeMysql( $val );
					}

					//remove last comma and space
					$query = rtrim( $query, "," );
					$paramsStr = rtrim( $paramsStr, ", " );
					$query .= " WHERE $where;";
					$evalStr .= "\"$bindType\"," .$paramsStr . ");";

					//setup statements
					$state = @$this->db->prepare( $query );
					//bind param call using eval
					@eval( $evalStr );
					//after bind then excute
					if( @$state->execute() ) {
						return true;
					} else {
						$this->lastError = $state->error;
						return false;
					}
				} else { //the record does not exist
					$query = "INSERT INTO $table (";
					$queryPart2 = '';
					foreach( $data as $key => $val ){
						$query .= $key . ',';
						$queryPart2 .= '?,';
						$bindType .= $this->getTypeMysql( $val );
						$paramsStr .= "\$data['$key'], ";
					}
					$query = rtrim( $query, ',' ); //remove the right comma
					$queryPart2 = rtrim( $queryPart2, ',' ); //remove the right comma
					$query .= ') VALUES (' . $queryPart2 . ')';
					//query should be like this at this point
					//INSERT INTO table (col1,col2,col3) VALUES (?,?,?)
					//remove last comma
					$paramsStr = rtrim( $paramsStr, ", " );
					//set up the eval string
					$evalStr .= "\"$bindType\"," .$paramsStr . ");";

					//setup statements
					$state = @$this->db->prepare( $query );
					//bind param call using eval
					@eval( $evalStr );
					//after bind then excute
					if( @$state->execute() ) {
						return true;
					} else {
						$this->lastError = $state->error;
						return false;
					}
				}
			}
		}

		/**
		 * translates php variables into bind_parm data-type strings
		 * @param $val
		 * @return string
		 */
		public static function getTypeMysql( $val ){
			$type = gettype( $val );
			if ( $type == 'string' ) {
				return's';
			} elseif( $type == 'double' ) {
				return 'd';
			} elseif( $type == 'integer' || $type == 'boolean' ){
				return 'i';
			} else {
				return 'b';
			}
		}
	}