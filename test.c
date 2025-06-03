
// echo $""
// echo $"HOME"
// // echo $''HOME
// echo $"HO""ME"
// echo $'HO''ME'
// echo $'HOME'
// echo $"HOLA"
// echo $'HOLA'

// <> syntax newline
// >>|>< syntax pipe
// echo > < syntax <
// echo | | syntax pipe

 // echo $UID

 // .echo.
 // export | grep "HOME"
 // export ""
 // export =
 // export 9HOLA=
 // export HOL@=bonjour
 // "export HOLA=""  bonjour  hey  ""echo """"""$HOLA"""""" | cat -e"


//"e"'c'ho hello

// apres avoir fait l expansion
// jai plusieurs tokens           e c ho hello

// je fais une fonction qui va parcourir la liste de tokens, qui va les merge en fonction de is_space ?
// while tokens if token->has_space cest un seul token donc lajouter dans un token dont le type est word sinon !has_space on merge

// token -> token -> token -> token -> token -> NULL



// gerer aussi le cas suivant :
// naankour@c2r11p1:~/minimerge2$ echo "$dawdaw" hello
//  hello
// naankour@c2r11p1:~/minimerge2$ echo $dawdaw hello
// hello
// naankour@c2r11p1:~/minimerge2$ echo $dawdaw hello
// et renvoyer cette nouvelle liste de tokens

// t_token	*ft_parsed(t_data *data)
// {
// 	data->tokens = lexer(data->line);
// 	free(data->line);
// 	data->line = NULL;
// 	if (ft_check_syntax_errors(data, data->tokens))
// 	{
// 		data->exit_code = 2;
// 		if (data->tokens)
// 		{
// 			free_token_list(data->tokens);
// 			data->tokens = NULL;
// 		}
// 		return (NULL);
// 	}
// 	data->tokens = ft_preprocess_dollar_quotes(data->tokens);
// 	data->tokens = expander(data->tokens, data);
// 	if (data->tokens)
// 		merge_tokens(&data->tokens);
// 	reassign_index(data->tokens);
// 	return (data->tokens);
// }

// /home/naankour/minimerge2$ echo $''HOME
//$HOME
///home/naankour/minimerge2$ echo $'HOME'
//$HOME

//echo"'hola'" command not found 