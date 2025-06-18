/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   miniRT.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: atreus <atreus@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 10:59:14 by gschwand          #+#    #+#             */
/*   Updated: 2025/06/18 12:52:26 by atreus           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H
# define M_PI 3.14159265358979323846
# include "../minilibx-linux/mlx.h"
# include "parsing.h"
# include <X11/keysym.h>
# include <error.h>
# include <fcntl.h>
# include <math.h>
# include <stdbool.h>
# include <stdio.h>
# include <string.h>
# include <unistd.h>

// Define EXIT_SUCCESS and EXIT_FAILURE if not already defined.
# ifndef EXIT_SUCCESS
#  define EXIT_SUCCESS 0
# endif

# ifndef EXIT_FAILURE
#  define EXIT_FAILURE 1
# endif

// EPSILON is a small threshold used to avoid issues with floating-point precision errors.
// It helps treat values close to zero as effectively zero.
# ifndef EPSILON 1e-6
#  define EPSILON 1e-6
# endif

#endif
