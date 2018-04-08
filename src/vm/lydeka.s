#/* ************************************************************************** */
#/*                                                                            */
#/*                                                        :::      ::::::::   */
#/*   lydeka.s                                           :+:      :+:    :+:   */
#/*                                                    +:+ +:+         +:+     */
#/*   By: mlu <mlu@student.42.fr>                    +#+  +:+       +#+        */
#/*                                                +#+#+#+#+#+   +#+           */
#/*                                                     #+#    #+#             */
#/*                                                    ###   ########.fr       */
#/*                                                                            */
#/* ************************************************************************** */

.name		"Lydeka"
.comment	"Tuturuu"

start:
	ld		%0, r5
	ld		%9, r15
	fork	%:stdspam
	fork	%:livespam

stdspam:
	live	%0
	add		r5, r15, r10
	sti		r5, r15, r10
	sti		r15, r5, r10
	fork	%:restore

restore:
	ld		%0, r5
	ld		%0, r15

livespam:
	live	%0
	zjmp	%:livespam

