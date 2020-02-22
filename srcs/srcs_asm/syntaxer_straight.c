//#include "asm.h"
//
//static uint8_t 		write_operation_code(t_cursor *p, t_lex *lx)
//{
//	t_int32			k;
//
//	k.num = get_operator(lx->lex);
//	int32_converter(p, sizeof(uint8_t), k, 0);
//	return (k.num);
//}
//
//
//static uint8_t 		handle_atypes(t_lex *lx, t_op_tab mod, int a)
//{
//	if ((lx->type == DIRECT || lx->type == DIRECT_LABEL)
//		&& mod.args_types[a] & T_DIR)
//		return (T_DIR);
//	else if ((lx->type == INDIRECT || lx->type == INDIRECT_LABEL)
//			 && mod.args_types[a] & T_IND)
//		return (T_IND);
//	else if (lx->type == REGISTER && mod.args_types[a] & T_REG)
//		return (T_REG);
//	else
//		argument_error(lx, mod.name);
//	return (0);
//}
//
//
//static size_t 		write_dir(t_cursor *p, t_lex *lx, t_op_tab mod)
//{
//	size_t 			xp;
//	t_int32			k;
//
//	if (lx->type == DIRECT)
//	{
//		k.num = core_atoi(lx->lex, lx);
//		int32_converter(p, mod.t_dir_size, k, 0);
//	}
//	else if (lx->type == DIRECT_LABEL)
//	{
//		if ((k.num = find_declared_labs(p, p->lab, lx->lex)) == 0)
//		{
//			xp = p->pos + 1 + ((mod.args_type_code) ? 1 : 0);
//			push_ref(p, lx, mod.t_dir_size, xp);
//		}
//		else
//			k.num = -k.num;
//		int32_converter(p, mod.t_dir_size, k, 0);
//	}
//	return (mod.t_dir_size);
//}
//
//static size_t 		write_ind(t_cursor *p, t_lex *lx, t_op_tab mod)
//{
//	size_t 			xp;
//	t_int32			k;
//
//	if (lx->type == INDIRECT)
//	{
//		k.num = core_atoi(lx->lex, lx);
//		int32_converter(p, sizeof(uint16_t), k, 0);
//	}
//	else if (lx->type == INDIRECT_LABEL)
//	{
//		if ((k.num = find_declared_labs(p, p->lab, lx->lex)) == 0)
//		{
//			xp = p->pos + 1 + ((mod.args_type_code) ? 1 : 0);
//			push_ref(p, lx, sizeof(uint16_t), xp);
//		}
//		else
//			k.num = -k.num;
//		int32_converter(p, sizeof(uint16_t), k, 0);
//	}
//	return (sizeof(uint16_t));
//}
//
//static t_lex 		*write_arguments(t_cursor *p, t_lex *lx, t_op_tab mod)
//{
//	t_int32 		k;
//	size_t 			tsize;
//	int 			i;
//
//	i = -1;
//	tsize = 0;
//	while (++i < mod.args_num)
//	{
//		if (lx->type == DIRECT || lx->type == DIRECT_LABEL)
//			tsize += write_dir(p, lx, mod);
//		else if (lx->type == INDIRECT || lx->type == INDIRECT_LABEL)
//			write_ind(p, lx, mod);
//		else if (lx->type == REGISTER)
//		{
//			k.num = core_atoi(lx->lex, lx);
//			int32_converter(p, sizeof(uint8_t), k, 0);
//			tsize += sizeof(uint8_t);
//		}
//		lx = lx->next;
//		if (i < mod.args_num - 1)
//			lx->type == SEPARATOR ? lx = lx->next : token_error(lx);
//	}
//	if (lx->type != NL)
//		token_error(lx);
//	p->pos += tsize + 1 + ((mod.args_type_code) ? 1 : 0);
//	return (lx);
//}
//
//t_lex 			*handle_name(t_cursor *p, t_lex *lx)
//{
////	if ((lx = skip_nl(lx)) && lx->type != COMMAND)
////		token_error(lx);
//	while (p->name == NULL || p->comment == NULL)
//	{
//		if (lx->next->type != STRING)
//			token_error(lx->next);
//		if (ft_strequ(lx->lex, NAME_CMD_STRING))
//		{
//			p->name = lx->next->lex;
//			if (ft_strlen(p->name) > PROG_NAME_LENGTH)
//				common_error(NAME_TOO_BIG);
//		}
//		else if (ft_strequ(lx->lex, COMMENT_CMD_STRING))
//		{
//			p->comment = lx->next->lex;
//			if (ft_strlen(p->comment) > COMMENT_LENGTH)
//				common_error(COMM_TOO_BIG);
//		}
//		lx = lx->next->next;
//		if (lx->type != NL)
//			token_error(lx);
//		lx = lx->next;
//	}
//	return (lx);
//}
//
//static t_lex		*handle_operations(t_cursor *p, t_lex *lx)
//{
//	uint8_t 		atypes[3] = {0, 0, 0};
//	t_lex 			*farg;
//	t_op_tab		mod;
//	uint8_t 		code;
//	int 			i;
//
//	code = write_operation_code(p, lx);
//	mod = op_tab[code - 1];
//	farg = lx->next;
//	lx = lx->next;
//	i = -1;
//	while (mod.args_type_code && ++i < mod.args_num)
//	{
//		atypes[i] = handle_atypes(lx, mod, i);
//		lx = lx->next;
//		if (i < mod.args_num - 1)
//			lx->type == SEPARATOR ? lx = lx->next : token_error(lx);
//	}
// 	write_atypes(p, atypes, mod.args_type_code);
//	display_grid(p->code->data, p->code->total, -1);
//	lx = write_arguments(p, farg, mod);
//	display_grid(p->code->data, p->code->total, -1);
//	return (lx);
//}
//
//void 				handle_expressions(t_cursor *p, t_lex *lx)
//{
//	p->pos = 0;
//	lx = handle_name(p, lx);
//	while ((lx = skip_nl(lx)) && lx->type != EOF)
//	{
//		if (lx->type == LABEL)
//		{
//			push_label(p, lx);
//			lx = lx->next;
//		}
//		else if (lx->type == INSTRUCTION)
//			lx = handle_operations(p, lx);
//		else
//			token_error(lx);
//	}
//	check_unused_refs(p, p->ref, p->lab);
//}
