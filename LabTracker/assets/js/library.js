/**
 * read a cookie from storage
 * @param name
 * @returns {*}
 */
$( document ).ready( () => {
    /******************************************************************************/
    /*******************************Modal Events***********************************/
    /******************************************************************************/
    modalEvents();
    function modalEvents(){
        $( document ).on( 'click', '.modal .close', function () {
            var modal = $( this ).closest( '.modal' );
            var id = $( modal ).attr( 'data-id' );
            closeModal( modal );
        } );

        //modal button events
        $( document ).on( 'click', '.modal input[type=button]', function () {
            var modal = $( this ).closest( '.modal' );
            var id = $( modal ).attr( 'data-id' );
            //get data for modal
            var data = window.modals.data[id].buttons;
            for ( i = 0; i < data.length; i++ ) {
                if ( data[i].value == $( this ).attr( 'value' ) ) {
                    //run the onclick
                    var cleanExit = true;
                    if ( data[i].onclick ) {
                        cleanExit = data[i].onclick( id );
                    }
                    if ( cleanExit ) {
                        closeModal( $( modal ) );
                    }
                }
            }
        } );

        //modal esc key event
        $( document ).on( 'keyup', function ( e ) {
            if ( window.modals.displaying ) {
                if ( e.keyCode == 27 ) {
                    if( !window.modals.data[window.modals.displaying].noExit ) {
                        closeModal( $( '.modal[data-id=' + window.modals.displaying + ']' ) );
                    }
                }
            }
        } );

        //modal reposition after resize
        $( window ).on( 'resize', function () {
            $( '.modal' ).each( function ( idx, elem ) {
                $( elem ).css( 'left', ( $( 'body' ).width() / 2 ) - ( $( elem ).width() / 2 ) + 'px' );
            } );
        } );

        //modal shadow click
        $( document ).on( 'click', '.modalShadow', function () {
            //check the data on it to make sure there is no override for this option
            var id = $( this ).attr( 'data-id' );
            var modal = window.modals.data[id];
            if ( modal.shadowClose ) {
                if ( isset( modal.shadowPrompt ) ) {
                    confirmModal( modal.shadowPrompt, function () {
                        closeModalId( id );
                        return true
                    }, undefined );
                } else {
                    closeModalId( id );
                }
            }
        } );

        /** dom structure
         * .tabWrapper
         *        .tabs
         *            .tab.active[data-tab]
         *            .tab[data-tab]
         *        .tabContent[data-tab]
         *        .tabContent.none[data-tab]
         */
        $( document ).on( 'click', '.tabWrapper .tab', function () {
            if ( $( this ).hasClass( 'active' ) ) return;
            var tab = $( this ).attr( 'data-tab' );
            var active = $( this ).siblings( '.active' );
            var activeTab = $( active ).attr( 'data-tab' );

            //change active tab to that you clicked
            $( active ).removeClass( 'active' );
            $( this ).addClass( 'active' );

            //switch the content tab
            $( '.tabContent[data-tab="' + tab + '"]' ).toggleClass( 'none' );
            $( '.tabContent[data-tab="' + activeTab + '"]' ).toggleClass( 'none' );
        } );
    }


    /******************************************************************************/
    /**************************** fake checkbox events ****************************/
    /******************************************************************************/
    function checkboxEvents() {
        $( document ).on( 'click', '.ui-checkbox a', function( e ){
            e.stopImmediatePropagation();
        } );
        $( document ).on( 'click', '.ui-checkbox', function(){
            //log( 'fired' );
            if( $( this ).attr( 'disabled' ) ) return;
            var input = $( this ).find( 'input') ;
            var i = $( '.clickable i', this );
            if( $( this ).attr( 'data-checked' ) == '1' ){
                //uncheck it
                i.remove();
                $( '.clickable', this ).append( '<i>&nbsp;</i>' );
                $( this ).attr( 'data-checked', '0' );
                $( input ).val( 0 ).trigger( 'change' );
            }
            else {
                if( $( this ).attr( 'data-indeterminate' ) == '1' && $( this ).attr( 'data-checked') != '2'  ){
                    i.remove();
                    $( '.clickable', this ).append( '<i class="fas fa-square" aria-hidden="true"></i>' );
                    $( this ).attr( 'data-checked', '2' );
                    $( input ).val( 2 ).trigger( 'change' );
                }
                else {
                    i.remove();
                    $( '.clickable', this ).append( '<i class="fas fa-check" aria-hidden="true"></i>' );
                    $( this ).attr( 'data-checked', '1' );
                    $( input ).val( 1 ).trigger( 'change' );
                }

            }
            return false;
        });
    }

});


window.modals = { ids: new Set(), data: {}, displaying: false };
/**
 * options structure
 * {
 *  title: "string", //the header for the title
 *  footer: true, //has a footer [optional]
 *  shadowClose: true, //clicking the shadow closes the modal [optional]
 *  shadowPrompt: "", //prompt for the user to close [optional]
 *  buttons: [ //buttons for footer
 *  	0 : {
 *  		value : "string", //value of the button
 *			name : "string", //name of the input [optional]
 *  		onclick : function(ModalId), //click event to run [optional]
 *  		class : "string" //class of the button for style or whatever [optional]
 *  		focus : true //focus on this button [optional],
 *  		disabled : true //button will be disabled [optional]
 *  	}
 *  ]
 * @param options
 */
function createModal( options ) {
    var id = 0;
    if ( window.modals.ids.length == 0 ) {
        id = 1;
    } else {
        id = window.modals.ids.peek() + 1;
    }

    if ( !isset( options['shadowClose'] ) ) {
        options['shadowClose'] = true;
    }

    if ( !isset( options['noExit'] ) ) {
        options['noExit'] = false;
    }

    if ( !isset( options['focus'] ) ) {
        options['focus'] = false;
    }

    if( !isset( options['wide'] ) ){
        options['wide'] = false;
    }

    var zIndex = ' style="z-index: ' + ( 10 + ( id - 1 ) ) + '" ';
    var html = '<div data-id="' + id + '" class="modal none"' + zIndex + '>' +
        '<div class="modalWrapper' + ( options['wide'] ? ' wide' : '' )+ '">';
    if ( options.title ) { //insert the header
        html += '<div class="modalHeaderWrapper"><div class="modalHeader clearfix">' +
            '<span class="title">' + options.title + '</span>';
        if( !options['noExit'] ) {
            html += '<span class="close">&times;</span>';
        }
        html += '</div></div>';
    }
    //insert the content section
    html += '<div class="modalContentWrapper"><div class="modalContent"></div></div>';

    if ( options.footer || options.buttons ) { //insert the header
        html += '<div class="modalFooterWrapper"><div class="modalFooter">';
        if ( options.buttons ) {
            for ( i = 0; i < options.buttons.length; i++ ) {
                var x = options.buttons[i];
                x.class = x.class ? x.class : '';
                x.name = x.name ? x.name : '';
                html += "<input " +
                    "type='button' " +
                    "value='" + x.value + "' " +
                    "class='" + x.class + "' " +
                    "name='" + x.name + "' " +
                    ( ( x.disabled ) ? ( "disabled=disabled" ) : ( '' ) ) +
                    ( ( x.focus ) ? 'autofocus />' : '/>' );
            }
        }
        
        html += '</div></div>';
    }
    $( 'body' ).append( '<div class="modalShadow none" data-id="' + id + '"' + zIndex + '>&nbsp;</div>' ).append( html );
    window.modals.data[id] = options;
    window.modals.ids.push( id );
    return $( '.modal[data-id=' + id + ']' );
}

function setModalContent( modal, html ) {
    $( modal ).find( '.modalContent' ).html( html );
}

function setModalContentAjax( modal, url, data, onSuccess ) {
    if( !isset( data ) ) data = null;
    setModalContent( modal, '<div class=margin10>'+ajaxLoaderBars( 10 )+'</div>' );
    $.post( url, data, function( d ){
        setModalContent( modal, d );
        $( 'select.autoload', modal ).each( function( i, elem ){
            var o = {};
            if( $( elem ).attr( 'search' ) && $( elem ).attr( 'search' ) == 'false' ){
                o['minimumResultsForSearch'] = Infinity;
            }
            $( elem ).select2(o);
        });
        if( isset( onSuccess ) ) {
            onSuccess();
        }
    });
}

function appendModalContent( modal, html ) {
    $( modal ).find( '.modalContent' ).append( html );
}

function appendModalContent( modal, html ) {
    $( modal ).find( '.modalContent' ).html( $( modal ).find( '.modalContent' ).html() + html );
}

function displayModal( modal, focusIndex ) {
    //center the modal on the screen
    var id = $( modal ).attr( 'data-id' );
    $( modal ).css( 'left', ( $( 'body' ).width() / 2 ) - ( $( modal ).width() / 2 ) + 'px' );
    $( modal ).css( 'top', ( $( document ).scrollTop() ) + 'px' );
    $( '.modalShadow[data-id=' + id + ']' ).fadeIn( 300 );
    $( modal ).fadeIn( 300 );
    //find focus if any exist
    var data = window.modals.data[id];
    if( data.buttons ) {
        for ( var i = 0; i < data.buttons.length; i++ ) {
            if ( data.buttons[i].focus ) {
                $( '.modal[data-id=' + id + '] input[name="' + data.buttons[i].name + '"]' ).focus();
                $( '.modal[data-id=' + id + '] input[value="' + data.buttons[i].value + '"]' ).focus();
            }
        }
    }
    //$('html, body').animate({
    //	scrollTop: $( modal ).offset().top
    //}, 200);
    //autoload select2 if present
    $( 'select.autoload', modal ).select2();
    window.modals.displaying = $( modal ).attr( 'data-id' );
}

function closeModalId( id ) {
    var modal = $( '.modal[data-id=' + id + ']' );
    delete window.modals.data[id];
    window.modals.ids.pop( id );
    if ( $( '.modal:not([data-id=' + id + '])' ).last().length ) {
        window.modals.displaying = $( '.modal' ).last().attr( 'data-id' );
    } else {
        window.modals.displaying = false;
    }
    $( modal ).fadeOut( 300, function () {
        $( modal ).remove();
    } );
    $( '.modalShadow[data-id=' + id + ']' ).fadeOut( 300, function () {
        $( this ).remove();
    } );
}

function closeModal( modal ) {
    //modal.find( '.modalWrapper' ).hide();
    var id = $( modal ).attr( 'data-id' );
    delete window.modals.data[id];
    window.modals.ids.pop( id );
    if ( $( '.modal:not([data-id=' + id + '])' ).last().length ) {
        window.modals.displaying = $( '.modal' ).last().attr( 'data-id' );
    } else {
        window.modals.displaying = false;
    }
    $( modal ).fadeOut( 300, function () {
        $( modal ).remove();
    } );
    $( '.modalShadow[data-id=' + id + ']' ).fadeOut( 300, function () {
        $( this ).remove();
    } );
}

function confirmModal( question, yesAction, noAction ) {
    var modal = createModal( {
        title: "Confirm",
        buttons: [
            {
                value: "Yes",
                onclick: yesAction
            },
            {
                value: "Cancel",
                onclick: noAction,
                class: 'redGlow'
            }
        ]
    } );
    setModalContent( modal, question );
    displayModal( modal );
    $( modal ).effect( 'shake' );
}

function errorModal( message, ut ) {
    var title = isset( ut ) ? ut : "Error";
    messageModal( message, title, true );
}

function messageModal( message, ut, error, action, shadowClose ) {
    error = isset( error ) ? error : false;
    var title = isset( ut ) ? ut : "Message";
    var struct = {
        title: title,
        buttons: [
            {
                value: "Ok",
                focus: true
            }
        ]
    };
    if( typeof shadowClose !== "undefined" ){
        struct.shadowClose = shadowClose;
    }
    if( typeof action === "function" ){
        struct.buttons[0].onclick = action;
    }
    var modal = createModal( struct );
    setModalContent( modal, message );
    displayModal( modal );
    if ( error )
        $( modal ).effect( 'shake' );
}

function messageModalAjax( ajax, title, error, action, shadowClose ){
    error = isset( error ) ? error : false;
    var ut = isset( title ) ? title : "Message";
    var struct = {
        title: ut,
        buttons: [
            {
                value: "Ok",
                focus: true
            }
        ]
    };
    if( typeof shadowClose !== "undefined" ){
        struct.shadowClose = shadowClose;
    }
    if( typeof action === "function" ){
        struct.buttons[0].onclick = action;
    }
    var modal = createModal( struct );
    setModalContentAjax( modal, ajax );
    displayModal( modal );
    if ( error )
        $( modal ).effect( 'shake' );
}


function readCookie( name ) {
    var cookiename = name + "=";
    var ca = document.cookie.split( ';' );
    for ( var i = 0; i < ca.length; i++ ) {
        var c = ca[i];
        while ( c.charAt( 0 ) == ' ' ) c = c.substring( 1, c.length );
        if ( c.indexOf( cookiename ) == 0 ) return decodeURIComponent( c.substring( cookiename.length, c.length ) );
    }
    return null;
}

/**
 * put a cookie into storage
 * @param name
 * @param data
 * @param days in days
 */
function setCookie( name, data, days ) {
    var expires = '';
    if ( days ) {
        var date = new Date();
        date.setTime( date.getTime() + ( days * 24 * 60 * 60 * 1000) );
        expires = '; expires=' + date.toUTCString();
    }
    document.cookie = name + "=" + data + expires + "; path=/";
}

/**
 * insert whole objects into localStorage JSON.stringifies for you
 * @param key
 * @param data
 * @returns {boolean}
 */
function setStorageJSON( key, data ) {
    if ( typeof(Storage) !== "undefined" ) {
        localStorage.setItem( key, JSON.stringify( data ) );
        return true;
    } else {
        return false;
    }
}

/**
 * insert whole objects into localStorage JSON.stringifies for you
 * @param key
 * @param data
 * @returns {boolean}
 */
function setSessionStorageJSON( key, data ) {
    if ( typeof(Storage) !== "undefined" ) {
        sessionStorage.setItem( key, JSON.stringify( data ) );
        return true;
    } else {
        return false;
    }
}

/**
 * Retrieve an object from localStroage JSON.parses for you
 * @param key
 * @returns {boolean}
 */
function getStorageJSON( key ) {
    if ( typeof(Storage) !== "undefined" ) {
        return JSON.parse( localStorage.getItem( key ) );
    } else {
        return false;
    }
}

/**
 * Retrieve an object from localStroage JSON.parses for you
 * @param key
 * @returns {boolean}
 */
function getSessionStorageJSON( key ) {
    if ( typeof(Storage) !== "undefined" ) {
        return JSON.parse( sessionStorage.getItem( key ) );
    } else {
        return false;
    }
}

/**
 * insert a string into localStorage
 * @param key
 * @param data
 * @returns {boolean}
 */
function setStorage( key, data ) {
    if ( typeof(Storage) !== "undefined" ) {
        localStorage.setItem( key, ( data ) );
        return true;
    } else {
        return false;
    }
}

/**
 * insert a string into localStorage
 * @param key
 * @param data
 * @returns {boolean}
 */
function setSessionStorage( key, data ) {
    if ( typeof(Storage) !== "undefined" ) {
        sessionStorage.setItem( key, ( data ) );
        return true;
    } else {
        return false;
    }
}

/**
 * retrieve a string from localStorage
 * @param key
 * @returns {boolean}
 */
function getStorage( key ) {
    if ( typeof(Storage) !== "undefined" ) {
        return localStorage.getItem( key );
    } else {
        return false;
    }
}

/**
 * retrieve a string from localStorage
 * @param key
 * @returns {boolean}
 */
function getSessionStorage( key ) {
    if ( typeof(Storage) !== "undefined" ) {
        return sessionStorage.getItem( key );
    } else {
        return false;
    }
}

/**
 * change url without refreshing page
 */
function updateUrl( url ) {
    history.pushState( null, null, url );
}

function stripQueryString() {
    var url = location.href;
    if ( url.indexOf( '?' ) > 0 ) {
        url = url.substr( 0, url.indexOf( '?' ) );
    } else {
        url = url.substr( 0, url.indexOf( '&' ) );
    }
    return url;
}
function queryStringToUrl( obj ) {
    var s = '';
    for ( x in obj ) {
        //this works in javascript
        //s += `${x}=${obj[x]}`;
        s += '&' + x + '=' + obj[x];
    }
    if ( s.length != 0 ) {
        s = '?' + s.substr( 1 );
    }
    return s;
}

function queryString( key, value ) {
    var obj = getQueryString();
    if ( value == null && obj[key] ) {
        delete obj[key];
    } else if ( value != null ) {
        obj[key] = value;
    }
    return obj;
}

function getQueryString() {
    var url = location.href;
    var vars;
    var obj = {};
    if ( url.indexOf( '?' ) == -1 && url.indexOf( '&' ) == -1 ) {
        return {};
    }
    if ( url.indexOf( '?' ) > 0 ) {
        vars = url.substr( url.indexOf( '?' ) + 1 );
    } else {
        vars = url.substr( url.indexOf( '&' ) + 1 );
    }
    var arr = vars.split( '&' );
    for ( var i = 0; i < arr.length; i++ ) {
        var s = arr[i];
        s = s.split( '=' );
        obj[s[0]] = s[1];
    }
    return obj;
}

function isset( value ) {
    if ( typeof value !== 'undefined' ) {
        return true;
    }
    return false;
}

function empty (mixedVar) {
    var undef;
    var key;
    var i;
    var len;
    var emptyValues = [undef, null, false, 0, '', '0'];

    for (i = 0, len = emptyValues.length; i < len; i++) {
        if (mixedVar === emptyValues[i]) {
            return true;
        }
    }

    if (typeof mixedVar === 'object') {
        for (key in mixedVar) {
            if (mixedVar.hasOwnProperty(key)) {
                return false;
            }
        }
        return true;
    }
    return false;
}


function log( args ) {
    console.log( args );
}

/**
 * optional value return. if arg is not set or is empty
 * @param arg value of item checking
 * @param repl value to opt as can be blank. if blank defaults to empty string
 * @returns {string|*}
 */
function opt( arg, repl ){
    if( isset( arg ) && !empty( arg ) ){
        return arg;
    }
    if( !isset( repl ) )
        return '';
    else
        return repl;
}

/**
 * verify a form's data
 * {
 *  formName : { regex: 'some-regex-test', msg: 'error msg' },
 *  pass : { regex: 'password', msg: "msg", confirm: true, confirmMsg: "Passwords must match" },
 *  strlenN: { strlen : { min : 0, max: 1 } },
 *  rangeN: { range : { min : 0, max: 1 } },
 *  exactN: { exact : 0 },
 *  lengthN: { length : 0 },
 * }
 * @param form
 * @param data
 * @returns {*}
 */
function verifyForm( form, data ) {
    //private util function to check if has confirm field
    function confirmCheck( dname, input ){
        let val = input.val();
        if ( dname.confirm ) {
            //check other confirm field
            let id = $( input ).attr( "data-confirm" );
            let otherVal = $( "#" + id ).val();
            if ( val != otherVal ) {
                return true;
            }
        }
        return false;
    }

    let hasError = false;
    let errors = [];
    let output = {
        msg: [],
        fields: []
    };
    for ( let name in data ) {
        let val;
        let input;
        //if passing the value thru the data else get from form
        if( data[name].val ){
            val = data[name].val;
        } else {
            input = $( '[name=' + name + ']', form );
            val = input.val();
        }
        //current data[name] being looked at cause im to lazy to type
        let dname = data[name];
        //console.log( name, input.val() );
        //check for a regex verify format
        if ( isset( dname.regex ) ) {
            if ( val.length === 0 || !data[name].regex.test( val ) ) {
                output.msg.push( dname.msg );
                output.fields.push( name );
                hasError = true;
            } else {
                if( confirmCheck( dname, input ) ){
                    output.msg.push( dname.confirmMsg );
                    output.fields.push( name );
                    hasError = true;
                }
            }
        }
        //check for a strlen verify format
        else if( isset( dname.strlen ) ){
            if( isset( dname.strlen.max ) ) {
                if ( !stringInRange( val, dname.strlen.min, dname.strlen.max ) ){
                    output.msg.push( dname.msg );
                    output.fields.push( name );
                    hasError = true;
                    if( confirmCheck( dname, input ) ){
                        output.msg.push( dname.confirmMsg );
                        output.fields.push( name );
                        hasError = true;
                    }
                    else {
                        if( confirmCheck( dname, input ) ){
                            output.msg.push( dname.confirmMsg );
                            output.fields.push( name );
                            hasError = true;
                        }
                    }
                }
            } else {
                if ( !stringInRange( val, dname.strlen.min ) ){
                    output.msg.push( dname.msg );
                    output.fields.push( name );
                    hasError = true;
                } else {
                    if( confirmCheck( dname, input ) ){
                        output.msg.push( dname.confirmMsg );
                        output.fields.push( name );
                        hasError = true;
                    }
                }
            }
        }
        //check for a range of numbers verify format
        else if( isset( dname.range ) ){
            if( isset( dname.range.max ) ) {
                if ( parseInt( val ) < dname.range.min || parseInt( val ) > dname.range.max ) {
                    output.msg.push( dname.msg );
                    output.fields.push( name );
                    hasError = true;
                } else {
                    if( confirmCheck( dname, input ) ){
                        output.msg.push( dname.confirmMsg );
                        output.fields.push( name );
                        hasError = true;
                    }
                }
            } else {
                if( parseInt( val ) < dname.range.min ) {
                    output.msg.push( dname.msg );
                    output.fields.push( name );
                    hasError = true;
                } else {
                    if( confirmCheck( dname, input ) ){
                        output.msg.push( dname.confirmMsg );
                        output.fields.push( name );
                        hasError = true;
                    }
                }
            }
        }
        else if( isset( dname.exact ) ) {
            if( val !== dname.exact ){
                output.msg.push( dname.msg );
                output.fields.push( name );
                hasError = true;
            }
        }
        else {
            if ( val.length === 0 ) {
                output.msg.push( dname.msg );
                output.fields.push( name );
                hasError = true;
            } else {
                if( confirmCheck( dname, input ) ){
                    output.msg.push( dname.confirmMsg );
                    output.fields.push( name );
                    hasError = true;
                }
            }
        }

    }

    if ( hasError ) {
        return output;
    } else {
        return false;
    }
}

function displayErrors( form, errorsDiv, data ) {
    errorsDiv.empty();
    if( data ) {
        for ( let i in data.msg ) {
            errorsDiv.append( "<p>" + data.msg[i] + "</p>" )
        }
    }
    $( 'input', form ).each( ( i, elem ) => {
        $( elem ).removeClass( 'error' );
        if( data ) {
            let name = $( elem ).attr( 'name' );
            if ( data.fields.indexOf( name ) !== -1 ) {
                $( elem ).addClass( 'error' );
            }
        }
    } );
}

function pluralString( int, single, plural ){
    if( !plural ){
        plural = 's';
    }
    if( int != 1 ){
        return single + plural;
    } else {
        return single;
    }

}

var whitespace = [
    ' ',
    '\n',
    '\r',
    '\t',
    '\f',
    '\x0b',
    '\xa0',
    '\u2000',
    '\u2001',
    '\u2002',
    '\u2003',
    '\u2004',
    '\u2005',
    '\u2006',
    '\u2007',
    '\u2008',
    '\u2009',
    '\u200a',
    '\u200b',
    '\u2028',
    '\u2029',
    '\u3000'
];
String.prototype.ucwords = function (){
    let s = this.toLocaleLowerCase();
    return s.replace( /\b[a-zA-Z]/g, (s) => s.toLocaleUpperCase() );
}
//php trim
String.prototype.trim = function ( chars ) {
    var ws = whitespace;
    ws.join( '' );
    var l = 0;
    var i = 0;
    str = this;
    str += '';

    if ( chars ) {
        ws = ( chars + '' ).replace( /([[\]().?/*{}+$^:])/g, '$1' );
    }

    l = str.length;
    for ( i = 0; i < l; i++ ) {
        if ( ws.indexOf( str.charAt( i ) ) === -1 ) {
            str = str.substring( i );
            break
        }
    }

    l = str.length;
    for ( i = l - 1; i >= 0; i-- ) {
        if ( whitespace.indexOf( str.charAt( i ) ) === -1 ) {
            str = str.substring( 0, i + 1 );
            break
        }
    }

    return whitespace.indexOf( str.charAt( 0 ) ) === -1 ? str : '';
};

String.prototype.ltrim = function ( chars ) {
    var ws = whitespace;
    ws.join( '' );
    var l = 0;
    var i = 0;
    str = this;
    str += '';

    if ( chars ) {
        ws = ( chars + '' ).replace( /([[\]().?/*{}+$^:])/g, '$1' );
    }

    l = str.length;
    for ( i = 0; i < l; i++ ) {
        if ( ws.indexOf( str.charAt( i ) ) === -1 ) {
            str = str.substring( i );
            break
        }
    }

    return whitespace.indexOf( str.charAt( 0 ) ) === -1 ? str : '';
};

String.prototype.rtrim = function ( chars ) {
    var ws = whitespace;
    ws.join( '' );
    var l = 0;
    var i = 0;
    str = this;
    str += '';

    if ( chars ) {
        ws = ( chars + '' ).replace( /([[\]().?/*{}+$^:])/g, '$1' );
    }

    l = str.length;
    for ( i = l - 1; i >= 0; i-- ) {
        if ( whitespace.indexOf( str.charAt( i ) ) === -1 ) {
            str = str.substring( 0, i + 1 );
            break
        }
    }

    return whitespace.indexOf( str.charAt( 0 ) ) === -1 ? str : '';
};

/**
 * get the length of string in bytes
 */
function getBytes(string) {
    var utf8length = 0;
    for (var n = 0; n < string.length; n++) {
        var c = string.charCodeAt(n);
        if (c < 128) {
            utf8length++;
        }
        else if((c > 127) && (c < 2048)) {
            utf8length = utf8length+2;
        }
        else {
            utf8length = utf8length+3;
        }
    }
    return utf8length;
}

function stringInRange( str, min, max ){
    if( max )
        return str.length >= min && str.length < max;
    else
        return str.length >= min;
}

/**
 * runs the action that is sent by ajax
 */
function ajaxAction( data ){
    if( data.action == 'redirect' ){
        if( window.onbeforeunload !== null ){
            removeConfirmLeave();
        }
        location.href = data.href;
    } else if( data.action === 'newWindow' ){
        window.open(
            data.href,
            '_blank' // <- This is what makes it open in a new window.
        );
    }
}

function rand( min, max ) {
    return Math.floor( Math.random() * (max - min) + min );
}

function randf( min, max ) {
    return ( Math.random() * (max - min) + min );
}

function tooltipHover( that ){
    var title = $( that ).attr( 'title' );
    if( !title ) return;
    $( that ).data( 'tipText', title ).removeAttr( 'title' );
    $( '<p class="tip"></p>' )
        .text( title )
        .appendTo( 'body' )
        .fadeIn( 'slow' );
}

function ajaxLoaderBars(){
    ajaxLoaderBars( 5 );
}
function ajaxLoaderBars( length ){
    var s = '<div class="ui-ajaxloader">';
    if( length > 10 ) length = 10;
    if( length < 2 ) length = 2;
    for( var i = 1; i <= length; i++ ){
        s+= '<div class="rect' + i + '"></div>';
    }
    s+= '</div>';
    return s;
}

/**
 * gets the locale of the user on chrome and firefox
 */
function getLocale() {
    if (navigator.languages != undefined) {
        if ( navigator.languages ) {
            var idx = navigator.languages.indexOf( "en-US" );
            if( idx != -1 ) {
                return navigator.languages[idx];
            }
            return navigator.languages[0];
        }
    } else
        return navigator.language;
}

function uses12Hour(){
    var date = new Date(Date.UTC(2012, 11, 12, 3, 0, 0));
    var dateString = date.toLocaleTimeString();

    if (dateString.match(/am|pm/i) || date.toString().match(/am|pm/i) ) {
        return true;
    }
    return false;
}

function daysInMonth (month, year) {
    return new Date(year, month, 0).getDate();
}

String.prototype.replaceAll = function(search, replacement) {
    var target = this;
    return target.replace(new RegExp(search, 'g'), replacement);
};

function ucwords( str ){
    str.toLowerCase().replace(/^[\u00C0-\u1FFF\u2C00-\uD7FF\w]|\s[\u00C0-\u1FFF\u2C00-\uD7FF\w]/g, function(letter) {
        return letter.toUpperCase();
    });
    return str;
}


function getInputsAsMap( dom ){
    let map = {};
    $( '[name]', dom ).each( (i, elem )=>{
        let type = $(elem).attr( 'type' );
        if( type === 'checkbox' ){
            map[ $(elem).attr('name') ] = $( elem ).prop( 'checked' );
        } else {
            map[$( elem ).attr( 'name' )] = $( elem ).val();
        }
    });
    return map;
}


var KeyCodes = {'BREAK' : 3,'BACKSPACE' : 8,'TAB' : 9,'CLEAR' : 12,'ENTER' : 13,'SHIFT' : 16,'CTRL' : 17,'ALT' : 18,'PAUSE/BREAK' : 19,'CAPS_LOCK' : 20,'HANGUL' : 21,'HANJA' : 25,'ESCAPE' : 27,'CONVERSION' : 28,'NON-CONVERSION' : 29,'SPACEBAR' : 32,'PAGE_UP' : 33,'PAGE_DOWN' : 34,'END' : 35,'HOME' : 36,'LEFT_ARROW' : 37,'UP_ARROW' : 38,'RIGHT_ARROW' : 39,'DOWN_ARROW' : 40,'SELECT' : 41,'PRINT' : 42,'EXECUTE' : 43,'PRINT_SCREEN' : 44,'INSERT' : 45,'DELETE' : 46,'HELP' : 47,'0' : 48,'1' : 49,'2' : 50,'3' : 51,'4' : 52,'5' : 53,'6' : 54,'7' : 55,'8' : 56,'9' : 57,':' : 58,'SEMICOLON_FIREFOX' : 59,'<' : 60,'EQUALS_FIREFOX' : 61,'SS' : 63,'@_FIREFOX' : 64,'A' : 65,'B' : 66,'C' : 67,'D' : 68,'E' : 69,'F' : 70,'G' : 71,'H' : 72,'I' : 73,'J' : 74,'K' : 75,'L' : 76,'M' : 77,'N' : 78,'O' : 79,'P' : 80,'Q' : 81,'R' : 82,'S' : 83,'T' : 84,'U' : 85,'V' : 86,'W' : 87,'X' : 88,'Y' : 89,'Z' : 90,'WINDOWS_KEY' : 91,'RIGHT_WINDOW_KEY' : 92,'CONTEXT_MENU' : 93,'SLEEP' : 95,'NUMPAD_0' : 96,'NUMPAD_1' : 97,'NUMPAD_2' : 98,'NUMPAD_3' : 99,'NUMPAD_4' : 100,'NUMPAD_5' : 101,'NUMPAD_6' : 102,'NUMPAD_7' : 103,'NUMPAD_8' : 104,'NUMPAD_9' : 105,'MULTIPLY' : 106,'ADD' : 107,'NUMPAD_PERIOD_FIREFOX' : 108,'SUBTRACT' : 109,'DECIMAL_POINT' : 110,'DIVIDE' : 111,'F1' : 112,'F2' : 113,'F3' : 114,'F4' : 115,'F5' : 116,'F6' : 117,'F7' : 118,'F8' : 119,'F9' : 120,'F10' : 121,'F11' : 122,'F12' : 123,'F13' : 124,'F14' : 125,'F15' : 126,'F16' : 127,'F17' : 128,'F18' : 129,'F19' : 130,'F20' : 131,'F21' : 132,'F22' : 133,'F23' : 134,'F24' : 135,'NUM_LOCK' : 144,'SCROLL_LOCK' : 145,'^' : 160,'!' : 161,'#' : 163,'$' : 164,'�' : 165,'PAGE_BACKWARD' : 166,'PAGE_FORWARD' : 167,'REFRESH' : 168,'CLOSING_PAREN_AZERTY' : 169,'*' : 170,'~ + * KEY' : 171,'HOME KEY' : 172,'MINUS_FIREFOX' : 173,'MUTE_UNMUTE' : 173,'DECREASE_VOLUME' : 174,'INCREASE_VOLUME' : 175,'NEXT' : 176,'PREVIOUS' : 177,'STOP' : 178,'PLAY/PAUSE' : 179,'E-MAIL' : 180,'MUTE_UNMUTE_FIREFOX_' : 181,'DECREASE_VOLUME_FIREFOX' : 182,'INCREASE_VOLUME_FIREFOX' : 183,'SEMI-COLON' : 186,'EQUAL_SIGN' : 187,'COMMA' : 188,'DASH' : 189,'PERIOD' : 190,'FORWARD_SLASH' : 191,'GRAVE_ACCENT' : 192,'/' : 193,'NUMPAD_PERIOD_CHROME' : 194,'OPEN_BRACKET' : 219,'BACK_SLASH' : 220,'CLOSE_BRACKET' : 221,'SINGLE_QUOTE' : 222,'`' : 223,'ALTGR' : 225,'LEFT_BACK_SLASH' : 226,'GNOME_COMPOSE_KEY' : 230,'XF86FORWARD' : 233,'XF86BACK' : 234,'NON-CONVERSION' : 235,'ALPHANUMERIC' : 240,'HIRAGANA/KATAKANA' : 242,'HALF-WIDTH/FULL-WIDTH' : 243,'KANJI' : 244,'UNLOCK_TRACKPAD' : 251,'TOGGLE_TOUCHPAD' : 255 };
var regex = {};
regex['section'] =/^[0-9]{5}$/;
regex['password'] = /.*(?=.{10,})(?=.*\d)(?=.*[a-z])(?=.*[A-Z])(?=.*[&"'(\-_)=~#{[|`\\^@\]}^$*???%,;:!?./?+]).*/;
regex['strongPassword'] = /^(?!.*(.)\1{1})(?=(.*[\d]){2,})(?=(.*[a-z]){2,})(?=(.*[A-Z]){2,})(?=(.*[@#$%!]){2,})(?:[\da-zA-Z@#$%!]){15,100}$/;
regex['email'] = /[a-z0-9!#$%&'*+/=?^_`{|}~-]+(?:\.[a-z0-9!#$%&'*+/=?^_`{|}~-]+)*@(?:[a-z0-9](?:[a-z0-9-]*[a-z0-9])?\.)+[a-z0-9](?:[a-z0-9-]*[a-z0-9])?/;
regex['name'] = /^[^0-9\.\,\"\?\!\;\:\#\$\%\&\(\)\*\+\-\/\<\>\=\@\[\]\\\^\_\{\}\|\~]{2,50}$/;
regex['customTime'] = /^(?:([0-2]?[0-9]) Days?, )?(?:([0-2]?[0-9]) Hours?, )?([0-5]?[0-9])\sMinutes?$/;
regex['sid'] = /^[0-9]{7}$/;
var CORE_URL = readCookie( 'url' );
