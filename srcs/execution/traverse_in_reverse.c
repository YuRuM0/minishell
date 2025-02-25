/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   traverse_in_reverse.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yulpark <yulpark@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 18:02:57 by yulpark           #+#    #+#             */
/*   Updated: 2025/02/25 19:10:38 by yulpark          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	tree_traverser()
{
	// if node = NULL, return prev code
		//why return prev code?
	// if node = pipe, handle it ->handle_pipe
	// if left child exists, go deeper down w/ recursion -> call tree_traverser( new treenode)
	// if node command, execute -> handle_redirection; command_executor
	// handle logic. op. -> handle_log_op
}

int handle_pipe()
{
	//create a pipe w/ two file descriptors, one for read/write
		// if fail, exit properly
	// fork left child process
	// execute the left child -> handle_pipe_left
		// redirect stdout to fd[1] so write in the pipe
	// fork right child process
		// if fail, exit properly
	// execute the right child -> handle_pipe_right
		//redirect stdout to fd[0] so read from the pipe
	//close the pipe in the parent
	//when right child done -> check with another function that returns status
		// return exist status of the right process
}
int command_executor()
{
	// expand the var; replace the env var in the command e.g. $HOME
	// construct the command & args; convert tokens into a proper cmd structure -> cmd_structurer
		//so that it is ready to execute??
	// handle redirections : <, >, <<, >>  -> redir_handler
	// call executor
	// if redir_handler fail then return fail
}

int handle_log_op()
{
	// check if the parent node is && or ||
		// if && execute the right side if condition met
		// if || execute the right side if condition failed
		// exit incase no logial operator
}


