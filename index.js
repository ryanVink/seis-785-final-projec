'use strict';
console.log('starting here');

var request = require("request");
var cheerio = require("cheerio");
var forEach = require("for-each");
var Particle = require('particle-api-js');
var particle = new Particle();

var d = new Date();
// var weekday = new Array(7);
// weekday[0]=  "Sun";
// weekday[1] = "Mon";
// weekday[2] = "Tue";
// weekday[3] = "Wed";
// weekday[4] = "Thu";
// weekday[5] = "Fri";
// weekday[6] = "Sat";
// var month = new Array(12);
// month[0] = "Jan";
// month[1] = "Feb";
// month[2] = "Mar";
// month[3] = "Apr";
// month[4] = "May";
// month[5] = "Jun";
// month[6] = "Jul";
// month[7] = "Aug";
// month[8] = "Sep";
// month[9] = "Oct";
// month[10] = "Nov";
// month[11] = "Dec";

var time = d.getHours() - 5;

var date = d.getDate() + 1;
if (time > 19) {
    date += 1;
}

var day = (d.getMonth() + 1) + '/' + (date) + '/' + d.getFullYear();



exports.handler = function (event, context, callback) {
    particle
        .login({username: 'ryan.vink@gmail.com', password: 'dshosty8*'})
        .then(
            function (data) {
                forEach([
                    {
                        'key': '0',
                        'value': 'http://www.opentable.com/avenida-minnetonka?m=46&p=2&d=' + day + '%207:00:00%20PM&r=190084&t=rest&rp=opentables.aspx&rid=190084'
                    },
                    {
                        'key': '1',
                        'value': 'http://www.opentable.com/birchs-on-the-lake-brewhouse-and-supperclub?m=46&p=2&d=' + day + '%207:00:00%20PM&r=169093&t=rest&rp=opentables.aspx&rid=169093'
                    },
                    {
                        'key': '2',
                        'value': 'http://www.opentable.com/cafe-lurcat-minneapolis?m=46&p=2&d=' + day + '%207:00:00%20PM&r=4747&t=rest&rp=opentables.aspx&rid=4747'
                    },
                    {
                        'key': '3',
                        'value': 'http://www.opentable.com/coalition?m=46&p=2&d=' + day + '%207:00:00%20PM&r=145876&t=rest&rp=opentables.aspx&rid=145876'
                    }
                ], function (value, index, array) {
                    console.log(value['value']);
                    request({
                        uri: value['value']
                    }, function (error, response, body) {
                        var $ = cheerio.load(body);
                        var total = 0;
                        $('.dtp-results-times li').each(function () {
                            if ($(this).text().length > 1) {
                                total += 1;
                            }
                        });
                        var color = 'RED~';
                        if (total > 0) {
                            color = 'YELLOW~';
                        }
                        if (total == 5) {
                            color = 'GREEN~';
                        }
                        particle.publishEvent({
                            name: 'event_update_led',
                            data: value['key'] + ":" + color,
                            auth: data.body.access_token
                        }).then(
                            function (data) {
                                if (data.statusCode == 200) {
                                    console.log("Event published successfully");
                                }
                            },
                            function (err) {
                                console.log("Failed to publish event: " + err);
                                callback("Failed to publish event: " + err);
                            });
                    });
                });
            });
};
