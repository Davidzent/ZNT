$( document ).ready( function () {
    if ( $( '#reportsReport' ).length > 0 ) {
        ReportsInit();
    }

    function ReportsInit() {
        $( document ).on( 'change', '#ReportsAction .daterangeterm', function ( e ) {
            SCDReports.call( this, e, 'daterange' );
        } );
        $( document ).on( 'change', '#ReportsAction .TermReport', function ( e ) {
            TermReports.call( this, e );
        } );
        $( document ).on( 'keyup || change', '#ReportsAction .studentterm', function ( e ) {
            SCDReports.call( this, e, 'student' );
        } );
        $( document ).on( 'keyup || change', '#ReportsAction .sectionterm', function ( e ) {
            SCDReports.call( this, e, 'section' );
        } );
        $( document ).submit( '#ReportsAction', function ( e ) {
            e.preventDefault();
        } );
        $(document ).on( 'click', '.result div.download a', function( e ){
            downloadCsv.call( this, e );
        } )
        $( '#DateReport' ).on( 'click', ( e ) => promptDate.call( this, e ) );
        $( '#StudentReport' ).on( 'click', ( e ) => promptStudent.call( this, e, false ) );
        $( '#StudentReportDetails' ).on( 'click', ( e ) => promptStudent.call( this, e, true ) );
        $( '#SectionReport' ).on( 'click', ( e ) => promptSection.call( this, e ) );
        $( '#TermReport' ).on( 'click', ( e ) => promptTerm.call( this, e ) );

        function downloadCsv( e ){
            e.preventDefault();

            let map = getInputsAsMap( $('.result') );
            log( map );

            let url = $( this ).attr( 'href' );
            $.ajax({
                type: 'POST',
                cache: false,
                url: url,
                data: map,
                xhr: () => {
                    var xhr = new XMLHttpRequest();
                    xhr.onreadystatechange = function () {
                        if (xhr.readyState === 2) {
                            if (xhr.status === 200) {
                                xhr.responseType = "blob";
                            } else {
                                xhr.responseType = "text";
                            }
                        }
                    };
                    return xhr;
                },
                //data: map, //form data
                success: ( d ) => {
                    fileName = 'report.csv';
                    //Convert the Byte Data to BLOB object.
                    var blob = new Blob([d], { type: "application/octetstream" });

                    //Check the Browser type and download the File.
                    var isIE = false || !!document.documentMode;
                    if (isIE) {
                        window.navigator.msSaveBlob(blob, fileName);
                    } else {
                        var url = window.URL || window.webkitURL;
                        link = url.createObjectURL(blob);
                        var a = $("<a />");
                        a.attr("download", fileName);
                        a.attr("href", link);
                        $("body").append(a);
                        a[0].click();
                        $(a).remove();
                    }
                }
            })
        }

        function promptTerm() {
            let results = $( '.adminphase2' );
            results.html( "" );
            results = $( '.filters' );
            results.html( "" );
            let form = $( '#ReportsAction' );
            let error = $( '.errors', form );
            error.html( "" );
            let map = { terms: 'term' };
            $.ajax( {
                type: 'POST',
                dataType: 'json',
                url: CORE_URL + $( form ).attr( 'action' ),
                data: map, //form data
                success: ( d ) => {
                    if ( d.success ) {
                        results = $( '.result' );
                        let html = '<select class="TermReport" name="TermReport">' +
                            '<option value="">Select a Term</option>';
                        let terms = d.data.terms;
                        for ( let i = 0; i < terms.length; i++ ) {
                            if ( terms[i].current ) {
                                html += '<option selected value="' + terms[i].term + '">' + terms[i].term + '</option>';
                            } else {
                                html += '<option value="' + terms[i].term + '">' + terms[i].term + '</option>';
                            }
                        }
                        html += '</select>';
                        html += '<div class="margin10 download"><a href="'+ CORE_URL + 'reports/download/term">Download Csv</a></div>';
                        results.html( html );
                        TermReports( null );
                    } else {
                        error.html( d.data.error );
                    }
                }
            } );
        }

        function promptSection() {
            let results = $( '.adminphase2' );
            results.html( "" );
            results = $( '.filters' );
            results.html( "" );
            let form = $( '#ReportsAction' );
            let error = $( '.errors', form );
            error.html( "" );
            let map = { terms: 'term' };
            $.ajax( {
                type: 'POST',
                dataType: 'json',
                url: CORE_URL + $( form ).attr( 'action' ),
                data: map, //form data
                success: ( d ) => {
                    if ( d.success ) {
                        results = $( '.result' );
                        let html = '<input class="sectionterm" placeholder="Section" type="text" name="section"/>' +
                            '<select class="sectionterm" name="term">' +
                            '<option value="">Select a Term</option>';
                        let terms = d.data.terms;
                        for ( let i = 0; i < terms.length; i++ ) {
                            if ( terms[i].current ) {
                                html += '<option selected value="' + terms[i].term + '">' + terms[i].term + '</option>';
                            } else {
                                html += '<option value="' + terms[i].term + '">' + terms[i].term + '</option>';
                            }
                        }
                        html += '</select><br>';
                        html += 'From: <input class="sectionterm"  type="datetime-local" name="startdate"/>'+
                            'To: <input class="sectionterm" type="datetime-local" name="enddate"/><br>';
                        html += '<div class="margin10 download"><a href="'+ CORE_URL + 'reports/download/section">Download Csv</a></div>';
                        results.html( html );
                    } else {
                        error.html( d.data.error );
                    }
                }
            } );
        }

        function promptStudent( e, details ) {
            let results = $( '.adminphase2' );
            results.html( "" );
            results = $( '.filters' );
            results.html( "" );
            let form = $( '#ReportsAction' );
            let error = $( '.errors', form );
            error.html( "" );
            let map = { terms: 'term' };
            $.ajax( {
                type: 'POST',
                dataType: 'json',
                url: CORE_URL + $( form ).attr( 'action' ),
                data: map, //form data
                success: ( d ) => {
                    if ( d.success ) {
                        results = $( '.result' );
                        let html = '<input class="studentterm" placeholder="Student ID" type="text" name="studentid"/>';
                        if ( details ) html += '<input type="hidden" name="studentDetails" value="1" />';
                        html += '<select class="studentterm" name="term">' +
                            '<option value="">Select a Term</option>';
                        let terms = d.data.terms;
                        for ( let i = 0; i < terms.length; i++ ) {
                            if ( terms[i].current ) {
                                html += '<option selected value="' + terms[i].term + '">' + terms[i].term + '</option>';
                            } else {
                                html += '<option value="' + terms[i].term + '">' + terms[i].term + '</option>';
                            }

                        }
                        html += '</select>';
                        if( !details )
                            html += '<div class="margin10 download"><a href="'+ CORE_URL + 'reports/download/student">Download Csv</a></div>';
                        else
                            html += '<div class="margin10 download"><a href="'+ CORE_URL + 'reports/download/studentDetails">Download Csv</a></div>';
                        results.html( html );
                    } else {
                        error.html( d.data.error );
                    }
                }
            } );
        }

        function promptDate() {
            let results = $( '.adminphase2' );
            results.html( "" );
            results = $( '.filters' );
            results.html( "" );
            let form = $( '#ReportsAction' );
            let error = $( '.errors', form );
            let map = { terms: 'term' };
            $.ajax( {
                type: 'POST',
                dataType: 'json',
                url: CORE_URL + $( form ).attr( 'action' ),
                data: map, //form data
                success: ( d ) => {
                    if ( d.success ) {
                        results = $( '.result' );
                        let html = 'From: <input class="daterangeterm"  type="datetime-local" name="startdate"/>' +
                            'To: <input class="daterangeterm" type="datetime-local" name="enddate"/><br>' +
                            '<select class="daterangeterm" name="term">' +
                            '<option value="">Select a Term</option>';
                        let terms = d.data.terms;
                        for ( let i = 0; i < terms.length; i++ ) {
                            if ( terms[i].current ) {
                                html += '<option selected value="' + terms[i].term + '">' + terms[i].term + '</option>';
                            } else {
                                html += '<option value="' + terms[i].term + '">' + terms[i].term + '</option>';
                            }
                        }
                        html += '</select>';
                        html += '<div class="margin10 download"><a href="'+ CORE_URL + 'reports/download/date">Download Csv</a></div>';
                        results.html( html );
                    } else {
                        error.html( d.data.error );
                    }
                }
            } );
        }

        //Student/Class/Date Total Hours for students (They basically are the same so I just made one for all of them)
        function SCDReports( e, option ) {
            e.preventDefault();
            let max = -1;
            let filters = 0;
            let form = $( '#ReportsAction' );
            let error = $( '.errors', form );
            let data = $( form ).serializeArray();
            let map = {};
            jQuery.each( data, function ( i, field ) {
                map[field.name] = field.value;
            } ); //get form data for verify
            let temp = false;
            //check the input
            if ( option === 'student' ) {
                let details = $( 'input[name=studentDetails]', form ).val();
                if ( map.studentid.length === 7 && map.term ) temp = true;
                if ( details === '1' )
                    map.details = 1;
                else
                    map.details = 0;
            } else if ( option === 'daterange' ) {
                if ( map.startdate && map.enddate && map.term ) temp = true;
                filters = 3;
            } else if ( option === 'section' ) {
                if ( map.section.length === 5 && map.term ) temp = true;
            }
            if ( temp ) {
                error.html( "" );
                $.ajax( {
                    type: 'POST',
                    dataType: 'json',
                    url: CORE_URL + $( form ).attr( 'action' ),
                    data: map, //form data
                    success: ( d ) => {
                        let display = 'adminphase2';
                        if ( d.dataType === 'raw' ) {
                            $( '.' + display ).html( d.data.data ).fadeIn();
                        } else {
                            //Table options
                            let th = ['First Name', 'Last Name', 'Student ID', 'Class', 'Section', 'Cumulative Hours'];
                            let reports = d.data.reports;
                            let checkbox = [];
                            let info = [
                                ['fname', 'firstname'],
                                ['lname', 'lastname'],
                                ['id', 'studentid'],
                                ['name', 'name'],
                                ['section', 'section'],
                                ['hours', 'cumulativehours'],
                            ];
                            let submitvals = false;
                            if ( d.success ) {
                                results = $( '.' + display );
                                results.fadeIn();
                                createtable( 'ReportsTable', th, checkbox, info, reports, submitvals, display, max, filters );
                            } else {
                                error.html( d.data.error );
                            }
                        }
                    }
                } );
            }
        }

        function TermReports( e ) {
            if ( e ) {
                e.preventDefault();
            }
            let form = $( '#ReportsAction' );
            let error = $( '.errors', form );
            let data = $( form ).serializeArray();
            let map = {};
            jQuery.each( data, function ( i, field ) {
                map[field.name] = field.value;
            } ); //get form data for verify
            error.html( "" );
            $.ajax( {
                type: 'POST',
                dataType: 'json',
                url: CORE_URL + $( form ).attr( 'action' ),
                data: map, //form data
                success: ( d ) => {
                    //Table options
                    let th = ['First Name', 'Last Name', 'Student ID', 'Class', 'Section', 'Cumulative Hours', 'Cumulative (hh:mm)'];
                    let reports = d.data.reports;
                    let weeks = d.data.weeks;
                    let checkbox = [];
                    let info = [
                        ['fname', 'firstname'],
                        ['lname', 'lastname'],
                        ['id', 'studentid'],
                        ['name', 'name'],
                        ['section', 'section'],
                        ['hours', 'cumulativehours'],
                        ['clkhours', 'clkhours'],
                    ];
                    for ( let i = 0; i < weeks; i++ ) {
                        th.push( 'Week ' + ( i + 1 ) );
                        info.push( ['week' + i, 'week' + ( i + 1 )] );
                    }
                    let submitvals = false;
                    let display = 'adminphase2';
                    max = -1;
                    filters = 0;
                    if ( d.success ) {
                        results = $( '.' + display );
                        results.fadeIn();
                        createtable( 'ReportsTable', th, checkbox, info, reports, submitvals, display, max, filters );
                    } else {
                        error.html( d.data.error );
                    }
                }
            } );
        }
    }
} );
