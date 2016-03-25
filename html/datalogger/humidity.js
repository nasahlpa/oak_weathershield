$(function() {
 
    var x_values = [];
    var y_values = [];
    var switch1 = true;
    $.get('data.php', {identifier: "humidity", time: set_time }, function(data) {
 
        data = data.split('/');
        for (var i in data)
        {
            if (switch1 == true)
            {
                x_values.push(data[i]);
                switch1 = false;
            }
            else
            {
                y_values.push(parseFloat(data[i]));
                switch1 = true;
            }
 
        }
        x_values.pop();
 
        $('#humidity').highcharts({
            chart : {
                type : 'spline'
            },
            title : {
                text : 'Humidity'
            },
            subtitle : {
                text : 'last 24h'
            },
            xAxis : {
                tickInterval:30,
                title : {
                    text : 'Time'
                },
                categories : x_values
            },
            yAxis : {
                min: 0,
                max: 100,
                tickInterval:10,
                title : {
                    text : 'Humidity'
                },
                labels : {
                    formatter : function() {
                        return this.value + "%"
                    }
                }
            },
            tooltip : {
                crosshairs : true,
                shared : true,
                valueSuffix : ''
            },
            exporting: { enabled: false },
            plotOptions : {
                spline : {
                    marker : {
                        radius : 4,
                        lineColor : '#666666',
                        lineWidth : 1
                    }
                }
            },
            series : [{
                showInLegend: false,
                name : 'Humidity',
                data : y_values
            }]
        });
    });
});
