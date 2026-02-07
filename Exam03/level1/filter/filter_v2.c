/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   filter_v2.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: chitoupa <chitoupa@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/07 21:05:08 by chitoupa          #+#    #+#             */
/*   Updated: 2026/02/07 21:15:33 by chitoupa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define _GNU_SOURCE  // Para memmem()
#ifndef BUFFER_SIZE
# define BUFFER_SIZE 42
#endif

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

// Función para encontrar y reemplazar todas las ocurrencias
void ft_filter(char *buffer, const char *target)
{
    int i = 0;
    int target_len = strlen(target);
    int j, k;

    /*
     * ALGORITMO DE BÚSQUEDA Y REEMPLAZO:
     * - Recorrer el buffer carácter por carácter
     * - En cada posición, verificar si coincide con el patrón
     * - Si coincide, escribir asteriscos y saltar la longitud del patrón
     * - Si no coincide, escribir el carácter original
     */
    
    while (buffer[i])
    {
        j = 0;
        // Verificar si hay coincidencia desde la posición actual
        while (target[j] && (buffer[i + j] == target[j]))
            j++;
        
        if (j == target_len) // Coincidencia completa encontrada
        {
            // Escribir asteriscos en lugar del patrón
            k = 0;
            while (k < target_len)
            {
                write(1, "*", 1);
                k++;
            }
            i += target_len; // Saltar el patrón completo
        }
        else
        {
            // No hay coincidencia, escribir carácter original
            write(1, &buffer[i], 1);
            i++;
        }
    }
}

int main(int argc, char **argv)
{
    /*
     * VALIDACIÓN DE ARGUMENTOS:
     * - Debe haber exactamente 1 argumento
     * - El argumento no puede estar vacío
     */
    if (argc != 2 || argv[1][0] == '\0')
        return 1;

    /*
     * LECTURA DINÁMICA DE STDIN:
     * - Usar buffer temporal para leer chunks
     * - Usar realloc() para expandir el buffer principal
     * - Mantener seguimiento del total leído
     */
    char temp[BUFFER_SIZE];
    char *result = NULL;
    char *buffer;
    int total_read = 0;
    ssize_t bytes;

    // Leer de stdin hasta EOF
    while ((bytes = read(0, temp, BUFFER_SIZE)) > 0)
    {
        // Expandir el buffer principal para acomodar los nuevos datos
        buffer = realloc(result, total_read + bytes + 1);
        if (!buffer)
        {
            free(result);
            perror("realloc");
            return 1;
        }
        
        result = buffer;
        
        // Copiar los nuevos datos al buffer principal
        memmove(result + total_read, temp, bytes);
        total_read += bytes;
        result[total_read] = '\0'; // Asegurar terminación
    }

    // Verificar errores de lectura
    if (bytes < 0)
    {
        perror("read");
        free(result);
        return 1;
    }

    // Si no se leyó nada, salir sin error
    if (!result)
        return 0;

    // Procesar el buffer y aplicar el filtro
    ft_filter(result, argv[1]);
    
    // Liberar memoria
    free(result);
    return 0;
}