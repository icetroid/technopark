/*$(document).ready(function(){
	
	var titles = ["Математики объяснили бесследное исчезновение малайзийского Боинга",
		"Google отметил дудлом день рождения выдающейся женщины-математика",
		"Гомер Симпсон предсказал массу Бозона Хиггса еще в 1998 году",
		"Младшеклассник поставил в тупик канцлера британского казначейства",
		"Британский математик вывел формулу идеальной пиццы"
	];
	var full_news = [
		"При помощи численных симуляций специалисты рассмотрели пять возможных сценариев развития событий с Boeing 777.",
		"Амалия Эмми Нетер - немецкий математик, \"самая крупная женщина-математик, когда-либо существовавшая\".",
		"Гомер пишет в одном из кадров на доске серию формул, первая из них с большой точностью дает массу бозона Хиггса.",
		"Канцлер британского казначейства Джордж Осборн не сказал сколько будет семью восемь.",
		"Известно, что от формы и размера пиццы зависит и ее вкус. Поэтому математик из Великобритании Евгения Ченг решила применить научный подход для определения оптимального размера этого блюда."
	];
	var newsPic = $("#news_pic");
	var newsText = $("#news_text");
	var currentNews = 0;
	setNews(0);
	function setNews(pos)
	{
		if(currentNews > 4)
		{
			pos = currentNews = 0;
		}
		if(currentNews < 0)
		{
			pos = currentNews = 4;
		}
		newsPic.css("backgroundImage", "url(img/news/" + pos + ".jpg)");
		newsText.html("<span id = \"title\">" + titles[pos] + "</span>" + "<br><span id = \"full_text\">" + full_news[pos] + "<span>");
		console.log(pos);
	}
	
	var interval = setInterval(function(){setNews(++currentNews)}, 3000);
	
	$("#next").click(function(){
		setNews(++currentNews);
		clearInterval(interval)
		interval = setInterval(function(){setNews(++currentNews)}, 3000);
	});
	$("#prev").click(function(){
		setNews(--currentNews);
		clearInterval(interval)
		interval = setInterval(function(){setNews(++currentNews)}, 3000);
	});
	
});


function animate_logo()
{
	var logo = $("#site_name");
	var origin = logo.html();
	
	var styles = {
		"bottom": "+=20px",
		"left": "+=50px",
		"font-size": "15px"
	};
	
	var back = {
		"bottom": "-=20px",
		"left": "-=50px",
		"font-size": "20px"
	};
	logo.animate(styles, 700).animate(back, 700);
	
	
	
	
}

*/
$( "#register" ).click(function() {
	
	var login = $("#login").val();
	$("#loginLabel").text("Login is correct");
	
	if(!login.match(/^[a-zA-Z0-9-_]{6,30}$/))
	{
		$("#loginLabel").text("Login: login must contain only alphanumeric characters, -, _, and have length from 6 to 30");
	}
	var email = $("#email").val();
	$("#emailLabel").text("Email: is correct");
	if(!email.match(/^[a-zA-Z0-9-_]+@[a-zA-Z0-9-_]+.[a-zA-Z]+$/))
	{
		$("#emailLabel").text("Email: is incorrect");
	}
	var nickname = $("#nickname").val();
	$("#nicknameLabel").text("nickname: is correct");
	if(!nickname.match(/^[a-zA-Z0-9-_\s]{6,30}$/))
	{
		$("#nicknameLabel").text("Nickname: must contain only alphanumeric characters, spaces, -, _, and have length from 6 to 30");
	}
	
	var pass = $("#password").val();
	var repeatPassword = $("#repeatPassword").val();
	$("#passwordLabel").text("Password: is correct");
	$("#repeatPasswordLabel").text("Passwords match");
	if(!pass.match(/^[a-zA-Z0-9]{6,30}$/))
	{
		$("#passwordLabel").text("Password: must contain only alphanumeric characters and have length from 6 to 30");
	}
	if(pass.localeCompare(repeatPassword))
	{
		$("#repeatPasswordLabel").text("Password don't match");
	}
	
});



