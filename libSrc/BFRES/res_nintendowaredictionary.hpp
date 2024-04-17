#pragma once

#include <cstdint>
#include <memory>
#include <cstring>

namespace vp::res {

	struct ResNintendoWareDictionary {
        struct ResDicNode {
            union {
                uint32_t     ref_bit;
                struct {
                    uint32_t ref_bit_rshift : 3;
                    uint32_t ref_bit_length : 29;
                };
            };
            int16_t        left_node;
            int16_t         right_node;
            const char *key; /* string starts at pos 2, 0-1 is a uint16_t of the string size */
        };
        static_assert(sizeof(ResDicNode) == 0x10);

        uint32_t       magic;
        int32_t        node_count; /* Note; does not include Root Node */
        ResDicNode     root_node;

        static constexpr inline uint32_t Magic = 0x5F444943;
        static constexpr inline int32_t NPos = -1;

        bool Build() {
            if (node_count < 0) {
                return true;
            }

            /* Find if we have an odd amount of nodes */
            int32_t odd_bit = (node_count + 1) & 1;
            ResDicNode *root_node_array = std::addressof(this->root_node);
            ResDicNode *current_node    = root_node_array;

            /* Default initialize our dictionary nodes in a double pattern */
            for (int32_t i = 0; i < (node_count + 1) - odd_bit; i = i + 2) {
                current_node[i + 0].ref_bit = NPos;
                current_node[i + 0].left_node = i;
                current_node[i + 0].right_node = i;
                current_node[i + 1].ref_bit = NPos;
                current_node[i + 1].left_node = i + 1;
                current_node[i + 1].right_node = i + 1;
            }
            /* Take care of odd node */
            if (odd_bit == 1) {
                current_node->ref_bit = NPos;
                current_node->left_node = node_count;
                current_node->right_node = node_count;
            }

            /* Main build loop */
            for (int32_t i = 1; i < node_count; ++i) {

                const char *i_key = root_node_array[i].key;
                const uint16_t i_key_len = *reinterpret_cast<const uint16_t*>(i_key);

                /* Traverse tree to insert location */
                uint16_t insert_index = this->root_node.left_node;
                uint32_t current_ref_bit = root_node_array[insert_index].ref_bit;
                uint32_t last_ref_bit = this->root_node.ref_bit;
                while (last_ref_bit < current_ref_bit) {
                    last_ref_bit = root_node_array[insert_index].ref_bit;

                    uint32_t ref_len = root_node_array[insert_index].ref_bit_length;
                    bool is_right_node = false;
                    if (ref_len < i_key_len) {
                        is_right_node = (i_key[i_key_len + ~ref_len + 2] >> root_node_array[insert_index].ref_bit_rshift) & 1;
                    }
                    insert_index = is_right_node ? root_node_array[insert_index].right_node : root_node_array[insert_index].left_node;

                    current_ref_bit = root_node_array[insert_index].ref_bit;
                }

                /* Pick out longer string */
                const int16_t insert_len = *reinterpret_cast<const uint16_t*>(root_node_array[insert_index].key);
                const int32_t longer_len = (insert_len <= i_key_len) ? i_key_len : insert_len;

                /* Null string is invalid */
                if (longer_len == 0) {
                    root_node_array[i].ref_bit = NPos;
                    return false;
                }

                /* Find ref bit */
                int32_t new_ref = 0;
                bool i_bit = false;
                bool insert_bit = false;
                while (i_bit == insert_bit) {
                    const int32_t new_ref_len = (new_ref >> 3);

                    if (new_ref_len < i_key_len) {
                        i_bit = (i_key[(i_key_len - new_ref_len) + 2] >> (new_ref & 7)) & 1;
                    } else {
                        i_bit = false;
                    }

                    if (new_ref_len < insert_len) {
                        insert_bit = (root_node_array[insert_index].key[(insert_len - new_ref_len) + 2] >> (new_ref & 7)) & 1;
                    } else {
                        insert_bit = false;
                    }

                    new_ref = new_ref + 1;
                    /* Two identical keys are invalid */
                    if ((longer_len << 3) - new_ref < 0) {
                        root_node_array[i].ref_bit = NPos;
                        return false;
                    }
                }

                /* Set current nodes ref_bit to the new ref */
                root_node_array[i].ref_bit = new_ref;
                if (new_ref == NPos) {
                    return false;
                }

                /* Get final node index */
                uint16_t last_index    = root_node.left_node;
                uint16_t interim_index = last_index;
                uint32_t last_ref      = root_node.ref_bit;
                while (last_ref < root_node_array[last_index].ref_bit) {
                    const uint32_t new_ref_len = (last_ref >> 3);
                    interim_index = last_index;

                    if (new_ref_len < i_key_len) {
                        i_bit = (i_key[(i_key_len - new_ref_len) + 2] >> (last_ref & 7)) & 1;
                    } else {
                        i_bit = false;
                    }

                    last_ref = root_node_array[last_index].ref_bit;
                    last_index = (i_bit == true) ? root_node_array[last_index].right_node : root_node_array[last_index].left_node;
                }

                uint32_t parent_len = root_node_array[interim_index].ref_bit_length;
                bool parent_rbit = false;
                if (parent_len < i_key_len) {
                    parent_rbit = (i_key[(i_key_len - parent_len) + 2] >> (root_node_array[interim_index].ref_bit_rshift)) & 1;
                } else {
                    parent_rbit = false;
                }
                std::addressof(root_node_array[interim_index].left_node)[parent_rbit] = static_cast<uint16_t>((reinterpret_cast<uintptr_t>(std::addressof(root_node_array[i])) - reinterpret_cast<uintptr_t>(std::addressof(this->root_node))) >> 4);

                uint32_t i_ref_len = root_node_array[i].ref_bit_length;
                bool i_rbit = false;
                if (i_ref_len < i_key_len) {
                    i_rbit = (i_key[(i_key_len - i_ref_len) + 2] >> (root_node_array[i].ref_bit_rshift)) & 1;
                } else {
                    i_rbit = false;
                }
                std::addressof(root_node_array[i].left_node)[i_rbit] = static_cast<uint16_t>((reinterpret_cast<uintptr_t>(std::addressof(root_node_array[last_index])) - reinterpret_cast<uintptr_t>(std::addressof(this->root_node))) >> 4);
            }

            return true;
        }

        uint32_t FindRefBit();

        int32_t FindEntryIndex(const char *key) const {

            /* Find key length */
            uint32_t len = 0;
            if (key != nullptr) {
                len = std::strlen(key);
            }

            /* Dictionary search */
            int16_t               next_idx  = root_node.left_node;
            const ResDicNode *node_iter = std::addressof(root_node) + next_idx;
            const ResDicNode *last_iter = std::addressof(root_node);
            int32_t               last_ref  = root_node.ref_bit;
            int32_t               iter_ref  = node_iter->ref_bit;
            while (last_ref < iter_ref) {
                const uint32_t ref_len = iter_ref >> 3;
                bool is_right = false;
                if (ref_len < len) {
                    is_right = key[len + ~ref_len] >> (iter_ref & 7) & 1;
                }
                last_iter = std::addressof(root_node) + next_idx;
                next_idx  = std::addressof(last_iter->left_node)[is_right];
                node_iter = std::addressof(root_node) + next_idx;
                last_ref  = last_iter->ref_bit;
                iter_ref  = node_iter->ref_bit;
            }

            /* Find larger string size */
            uint16_t key_len = *reinterpret_cast<const uint16_t*>(node_iter->key);
            uint16_t max_len = len;
            if (key_len <= len) {
                max_len = key_len;
            }

            /* Ensure strings are identical */
            if (max_len == 0 && key_len < len) { return -1; }
            const int32_t result = ::memcmp(node_iter->key + 2, key, max_len);
            if (result != 0)   { return -1; }
            if (len < key_len) { return -1; }
            if (key_len < len) { return -1; }

            /* Find entry index through ptrdiff */
            ptrdiff_t ptr_diff = reinterpret_cast<uintptr_t>(node_iter) - sizeof(ResNintendoWareDictionary) - reinterpret_cast<uintptr_t>(this);
            if ((~ptr_diff & 0xf'ffff'fff0) != 0) {
                return ptr_diff >> 4;
            }
            return -1;
        }

        const char *FindKeyByEntryIndex(uint32_t entry_id) const {
            return (std::addressof(root_node) + 1)[entry_id].key + 2;
        }
    };
    static_assert(sizeof(ResNintendoWareDictionary) == 0x18);
}
