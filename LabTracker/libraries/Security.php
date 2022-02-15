<?php

	/**
	 * Copyright (C) Michael Risher - All Rights Reserved
	 * Unauthorized copying of this file, via any medium is strictly prohibited
	 * Proprietary and confidential
	 * Written by Michael Risher <rishermichael@gmail.com>, 2/3/2018 23:13
	 */
	class Security {
		/**
		 * clean strings of bad stuffs
		 * @param mixed $string
		 * @param bool|false $allowhtml
		 * @param bool|false $limit_range
		 * @return mixed|string
		 */
		public static function sanitize( $string, $allowhtml = false, $limit_range = false ) {
			if( gettype($string) == "array" ){
				return Security::sanitizePost( $string, $allowhtml, $limit_range );
			}
			$string = (string)$string;

			if ($limit_range) {
				$string = preg_replace('/[^(\t\x0-\x7F)]*/','', $string);
			}

			//get_magic_quotes_gpc() has been removed in php 8.0 and is no longer needed since upgrade from 5.4 php on old server.
            $string = trim($string);

			if ( !$allowhtml ) {
				$invalid = array('@<script[^>]*?>.*?</script>@si', '@<[\/\!]*?[^<>]*?>@si', '@<style[^>]*?>.*?</style>@siU', '@<![\s\S]*?--[ \t\n\r]*>@');
				$string = preg_replace($invalid, '', $string);
			}
			return $string;
		}

		/**
		 * clean strings of bad stuffs
		 * @param array $post
		 * @param bool|false $allowhtml
		 * @param bool|false $limit_range
		 * @return mixed|string
		 */
		private static function sanitizePost( $post, $allowhtml = false, $limit_range = false ) {
			foreach( $post as $key => $value ){
				$post[$key] = Security::sanitize( $post[$key], $allowhtml, $limit_range );
			}
			return $post;
		}

		/**
		 * get a time salted sha1
		 * @param $data
		 * @return string
		 */
		public static function timeSaltedSha1( $data ){
			return sha1( $data . microtime() );
		}

		/**
		 * creates the user password using their passed password and username
		 * @param $inPass
		 * @param $inUser
		 * @return string
		 */
		public static function hashPassword( $inPass, $inUser ){
			$password[0] = hash( 'sha512', substr( $inPass, 0, 64 ) );
			$password[1] = hash( 'sha512', substr( $inPass, 64 ) );
			$passwordHash = hash( 'sha512', $password[0] . $password[1] . $inUser );
			return $passwordHash;
		}

		/**
		 * rc4 encryption faster than the aes encryption
		 * @param $key salt
		 * @param $str string encrypting
		 * @return string
		 */
		function rc4($key, $str) {
			$s = array();
			for ($i = 0; $i < 256; $i++) {
				$s[$i] = $i;
			}
			$j = 0;
			for ($i = 0; $i < 256; $i++) {
				$j = ($j + $s[$i] + ord($key[$i % strlen($key)])) % 256;
				$x = $s[$i];
				$s[$i] = $s[$j];
				$s[$j] = $x;
			}
			$i = 0;
			$j = 0;
			$res = '';
			for ($y = 0; $y < strlen($str); $y++) {
				$i = ($i + 1) % 256;
				$j = ($j + $s[$i]) % 256;
				$x = $s[$i];
				$s[$i] = $s[$j];
				$s[$j] = $x;
				$res .= $str[$y] ^ chr($s[($s[$i] + $s[$j]) % 256]);
			}
			return $res;
		}

	}