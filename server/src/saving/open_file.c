#include "../../include/my.h"
#include "../../include/utils.h"
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>

uint16_t hash(const char *const data_str, unsigned int size)
{
    uint16_t crc = 65535;
    uint32_t pos = 0;

    while (size != 0) {
        crc ^= (char) data_str[pos] << 8;
        pos++;
        for (unsigned int i = 0; i < 8; i++) {
            crc = crc & 0x8000 ? (crc << 1) ^ 0x1021 : crc << 1;
        }
        size -= 1;
    }
    return crc;
}

save_data_t read_save(void)
{
    int fd = open("save.dat", O_RDONLY);
    save_data_t save = {0};
    struct stat stats;
    uint16_t hash_val;

    if (fd < 0) {
        error("Error while opening save file");
        return save;
    }
    stat("save.dat", &stats);
    if (stats.st_size != sizeof(save_data_t) + sizeof(uint16_t))
        error("Save file size differs from expected size");
    read(fd, &save, sizeof(save_data_t));
    read(fd, &hash_val, sizeof(uint16_t));
    if (hash((char *)&save, sizeof(save_data_t)) != hash_val)
        error("Save file is corrupted");
    close(fd);
    return save;
}

void write_save(save_data_t save)
{
    uint16_t hash_val;
    int fd = open("save.dat", O_WRONLY | O_CREAT, S_IRUSR | S_IWUSR);

    if (fd < 0)
        error("Error while trying to write save data");
    write(fd, &save, sizeof(save_data_t));
    hash_val = hash((char *)&save, sizeof(save_data_t));
    write(fd, &hash_val, sizeof(uint16_t));
    close(fd);
}
