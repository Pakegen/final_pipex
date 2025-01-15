void limited_read_write(int input_fd, int output_fd)
{
    char buffer[BUFFER_SIZE];
    ssize_t bytes_read, total_bytes = 0;

    while ((bytes_read = read(input_fd, buffer, BUFFER_SIZE)) > 0)
    {
        if (total_bytes + bytes_read > MAX_BYTES)
        {
            write(output_fd, buffer, MAX_BYTES - total_bytes);
            break;
        }
        write(output_fd, buffer, bytes_read);
        total_bytes += bytes_read;
    }

    if (bytes_read == -1)
        error_exit("ERROR: Failed to read input\n");
} pour le timeout.
